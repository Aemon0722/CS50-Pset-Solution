import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from datetime import datetime, date


# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        name = request.form.get("name")
        birthday = request.form.get("birthday")

        # validate input
        if not name or not birthday:
            return render_template("index.html", message="missing input")

        # turn birthday into datetime object
        date_object = datetime.strptime(birthday, "%Y-%m-%d")
        today = datetime.today()

        # validate date
        if date_object > today:
            return render_template("index.html", message="invalid birthday")

        date = birthday.split("-")
        month = date[1]
        day = date[2]

        # TODO: Add the user's entry into the database
        db.execute("INSERT INTO birthdays (name, month, day) VALUES(?,?,?)", name, month, day)
        return redirect("/")

    else:
        rows = db.execute("SELECT name, month, day FROM birthdays")

        # TODO: Display the entries in the database on index.html

        return render_template("index.html", rows=rows)


@app.route("/search", methods=["GET", "POST"])
def search():
    q = request.args.get("q")
    if q:
        rows = db.execute("SELECT name, month, day FROM birthdays WHERE name LIKE ?", "%" + q + "%")
    else:
        rows = []
    return  render_template("index.html", rows=rows)

