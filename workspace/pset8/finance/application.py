# export API_KEY=pk_71c8895a76ad4e72ac449501ae9bcd3e
import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
# export API_KEY=pk_71c8895a76ad4e72ac449501ae9bcd3e
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE id = :user_id GROUP BY symbol HAVING total_shares > 0", user_id=session["user_id"])
    users = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])[0]["cash"]

    current_prices = {}

    grand_total = 0

    for stock in stocks:
        current_prices[stock["symbol"]] = lookup(stock["symbol"])
        grand_total = grand_total + (lookup(stock["symbol"])["price"] * stock["total_shares"])

    grand_total = grand_total + cash

    return render_template("index.html", stocks=stocks, cash=cash, current_prices=current_prices, grand_total=grand_total)


@app.route("/add", methods=["GET", "POST"])
@login_required
def add():
    """Adds cash to account"""
    if request.method == "POST":
        if not request.form.get("amount"):
            return apology("must provide amount")
        amount = float(request.form.get("amount"))
        if amount <= 0:
            return apology("Provide valid amount", 400)
        cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])[0]["cash"]
        new_cash = cash + amount
        deposit_name = "CASH"
        # db.execute("INSERT INTO transactions (id, symbol, name shares, price) VALUES (:user_id, :symbol, :quantity, :price)",
        #           user_id=session["user_id"],
        #           symbol=deposit_name,
        #           quantity=1,
        #           price=amount)

        db.execute("UPDATE users SET cash = :new_cash WHERE id = :user_id",
                   new_cash=new_cash,
                   user_id=session["user_id"])
        return redirect("/")
    else:
        return render_template("add.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        api_response = lookup(request.form.get("symbol"))
        if not api_response:
            return apology("Please provide valid symbol", 400)
        # shares = int(request.form.get("shares"))
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("shares must be a posative integer", 400)
        if shares <= 0:
            return apology("Please provide valid number of shares", 400)
        total_cost = float(api_response["price"])*shares
        rows = db.execute("SELECT * FROM users WHERE id = :user_id", user_id=session["user_id"])
        if(total_cost > float(rows[0]["cash"])):
            return apology("You have insufficient funds", 400)
        db.execute("UPDATE users SET cash = cash - :total_cost WHERE id = :user_id",
                   total_cost=total_cost, user_id=session["user_id"])
        db.execute("INSERT INTO transactions (id, symbol, price, shares) VALUES(:user_id, :symbol, :price, :shares)",
                   user_id=session["user_id"],
                   symbol=api_response["symbol"],
                   price=api_response["price"],
                   shares=shares)
        flash("Order Completed!")
        # Redirect user to home page
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/check", methods=["GET"])
def check():
    """Return true if username available and 1 character or more, else false, in JSON format"""
    rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.args.get("username"))

    if len(request.args.get("username")) > 0 and len(rows) == 0:
        return jsonify(True)
    else:
        return jsonify(False)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute(
        "SELECT symbol, shares, price, created FROM transactions WHERE id = :user_id ORDER BY created ASC", user_id=4)
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        symbol_quote = lookup(request.form.get("symbol"))
        if not symbol_quote:
            return apology("Please provide valid symbol", 400)

        return render_template("quoted.html", symbol_quote=symbol_quote)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    if request.method == "POST":

        if not request.form.get("username"):
            return apology("Please provide username", 400)

        elif not request.form.get("password"):
            return apology("Please provide password", 400)

        elif not request.form.get("confirmation"):
            return apology("Please provide confirmation password", 400)

        if not request.form.get("password") == request.form.get("confirmation"):
            return apology("Passwords do not match", 400)

        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        if len(rows) != 0:
            return apology("Username unavailable", 400)

        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
                   username=request.form.get("username"),
                   hash=generate_password_hash(request.form.get("password")))

        flash("Registered!")
        return redirect("/")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        api_response = lookup(request.form.get("symbol"))
        if not api_response:
            return apology("Please select a symbol", 400)

        shares = int(request.form.get("shares"))
        if shares <= 0:
            return apology("Please provide valid number of shares", 400)

        # Query database to identify number of shares available for sale
        stock = db.execute("SELECT SUM(shares) as total_shares FROM transactions WHERE id = :user_id AND symbol = :symbol GROUP BY symbol",
                           user_id=session["user_id"], symbol=request.form.get("symbol"))

        if len(stock) != 1 or stock[0]["total_shares"] <= 0 or stock[0]["total_shares"] < shares:
            return apology("You have insufficient shares", 400)

        rows = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])

        cash_before = rows[0]["cash"]

        new_cash = (api_response["price"] * shares) + cash_before

        db.execute("UPDATE users SET cash = :new_cash WHERE id = :user_id", new_cash=new_cash, user_id=session["user_id"])
        db.execute("INSERT INTO transactions (id, symbol, shares, price) VALUES(:user_id, :symbol, :shares, :price)",
                   user_id=session["user_id"],
                   symbol=request.form.get("symbol"),
                   shares=-shares,
                   price=api_response["price"])
        flash("Sold!")

        # Redirect user to login form
        return redirect("/")
    else:
        stocks = db.execute(
            "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE id = :user_id GROUP BY symbol HAVING total_shares > 0", user_id=session["user_id"])
        return render_template("sell.html", stocks=stocks)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)