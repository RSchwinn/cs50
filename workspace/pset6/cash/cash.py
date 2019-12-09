from cs50 import get_float

total = round(get_float("Change owed:") * 100)

if total < 0:
    total = round(get_float("Change owed:") * 100)

quarters = total // 25
left_over = total - quarters * 25

dimes = left_over // 10
left_over = left_over - dimes * 10

nickels = left_over // 5
left_over = left_over - nickels * 5

total_coins = quarters + dimes + nickels + left_over

print(total_coins)