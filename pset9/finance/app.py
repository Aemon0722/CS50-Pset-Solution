import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
from datetime import datetime


# Configure application
app = Flask(__name__)
app.debug = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():

    # show username
    username = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])[0]["username"]

    # get all the symbol and its quantity owned by the user
    portfolio = db.execute("SELECT symbol, SUM(quantity) FROM history WHERE user_id = ? GROUP BY symbol", session["user_id"])
    instrument_total = 0
    for symbol in portfolio:
        price = lookup(symbol["symbol"])["price"]
        symbol["price"] = price
        symbol["value"] = price*symbol["SUM(quantity)"]
        instrument_total += symbol["value"]

    total_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    total = instrument_total + total_cash
    return render_template("index.html", username=username, cash=usd(total_cash), portfolio=portfolio,
                           instrument_total=usd(instrument_total), total_liquidity=usd(total), usd=usd)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")
    else:
        symbol = request.form.get("symbol").upper()


        # prevent user input non-numeric string
        try:
            number = int(request.form.get("shares"))
        except ValueError:
            return apology("Incorrect input")

        quote = lookup(symbol)

        # when user did not input symbol or number of share
        if not symbol or not number:
            return apology("Input is blank")


        # when user input number of share that is less than 1
        if number < 0:
            return apology("Invalid number of share")


        # when the symbol cannot be found
        if quote is None:
            return apology("Symbol not found")
        # purchase the stock
        else:
            cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
            proceeds = quote["price"]*number
            # check if current cash is sufficient
            if proceeds > cash:
                return apology("Insufficient cash")
            else:
                t_date = datetime.now()
                db.execute("INSERT INTO history(user_id, symbol, date_time, quantity, t_price, proceeds) VALUES (?,?,?,?,?,?)",
                           session["user_id"], symbol, t_date, number, quote["price"], -proceeds)
                remaining = cash - proceeds
                db.execute("UPDATE users SET cash = ? WHERE id = ?", remaining, session["user_id"])
                return redirect("/")


@app.route("/history")
@login_required
def history():
    history = db.execute("SELECT date_time, symbol, t_price, quantity FROM history WHERE user_id = ? ORDER BY date_time DESC", session["user_id"])
    return render_template("history.html", history=history, usd=usd)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

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
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        if quote is None:
            return apology("Stock not found")
        else:
            price = quote["price"]

        return render_template("quoted.html", symbol=symbol, price=price, usd=usd)


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")
    else:
        username = request.form.get("username")
        password = request.form.get("password")
        cfm_password = request.form.get("confirmation")

        # if any one of the input is blank
        if not username or not password or not cfm_password:
            return apology("Input is blank")

        # if the password does not match with confirm_password
        if password != cfm_password:
            return apology("Passwords do not match")

        # Try to register user if the username is not duplicate
        h_password = generate_password_hash(password)
        try:
            db.execute("INSERT INTO users (username, hash) VALUES(?,?)", username, h_password)
            return redirect("/login")
        except ValueError:
             return apology("User already existed")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():

    if request.method == "GET":
        portfolio = db.execute("SELECT symbol FROM history WHERE user_id = ? GROUP BY symbol HAVING SUM(quantity) > 0", session["user_id"])
        return render_template("sell.html", portfolio=portfolio)
    else:
        symbol = request.form.get("symbol")

        try:
            number = int(request.form.get("shares"))
        except ValueError:
            return apology("Incorrect Input")

        shares = db.execute("SELECT SUM(quantity) FROM history WHERE symbol = ? AND user_id = ? GROUP BY symbol", symbol, session["user_id"])

        # if the user do not have enough stock
        if shares[0]["SUM(quantity)"] < number:
            return apology("You do not have sufficient stock to sell")
        else:
            # current time = transaction date
            t_date = datetime.now()
            price = lookup(symbol)["price"]

            # realized amount
            realized = price*number
            cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

            # update new data into history table
            db.execute("INSERT INTO history(user_id, symbol, date_time, quantity, t_price, proceeds) VALUES (?,?,?,?,?,?)",
                        session["user_id"], symbol, t_date, -number, price, realized)

            # update cash
            db.execute("UPDATE users SET cash = ? WHERE id = ?", realized + cash, session["user_id"])
            return redirect("/")


@app.route("/account")
def account_setting():
    username = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])[0]["username"]
    return render_template("account.html", username=username)


@app.route("/password", methods=["GET","POST"])
def change_password():
    if request.method == "GET":
        return render_template("password.html")
    else:
        old_password = request.form.get("old_pw")
        exist_password = db.execute("SELECT hash FROM users WHERE id = ?", session["user_id"])[0]["hash"]
        new_password = request.form.get("password")
        cfm_password = request.form.get("confirmation")

        if not old_password or not new_password or not cfm_password:
            return apology("Input is blank")

        if not check_password_hash(exist_password, old_password):
            return apology("Wrong Password")

        if new_password != cfm_password:
            return apology("Passwords do not match")

        h_password = generate_password_hash(new_password)
        db.execute("UPDATE users SET hash = ? WHERE id = ?", h_password, session["user_id"])
        return redirect("/account")

