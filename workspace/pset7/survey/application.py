import cs50
import csv

from flask import Flask, jsonify, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Reload templates when they are changed
app.config["TEMPLATES_AUTO_RELOAD"] = True


@app.after_request
def after_request(response):
    """Disable caching"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET"])
def get_index():
    return redirect("/form")


@app.route("/form", methods=["GET"])
def get_form():
    return render_template("form.html")


@app.route("/form", methods=["POST"])
def post_form():
    if not request.form.get("username"):
        return render_template("error.html", message="Missing username")

    if not request.form.get("exampleRadios"):
        return render_template("error.html", message="Missing checkbox entry")

    if not request.form.get("selection"):
        return render_template("error.html", message="Missing selection")

    username = request.form.get("username")
    exampleRadios = request.form.get("exampleRadios")
    selection = request.form.get("selection")

    with open("survey.csv", "a") as survey:
        surveyobject = csv.writer(survey)
        surveyobject.writerow((username, exampleRadios, selection))
    return redirect("/sheet")


@app.route("/sheet", methods=["GET"])
def get_sheet():
    with open("survey.csv", "r") as saved_surveys:
        the_data = csv.reader(saved_surveys)
        table_data = list(the_data)

    return render_template("results.html", table_data=table_data)
