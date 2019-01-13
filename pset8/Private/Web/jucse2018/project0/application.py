import os
import requests

from flask import Flask, session, request, render_template
from flask_session import Session
from tempfile import mkdtemp
from sqlalchemy import create_engine
from sqlalchemy.orm import scoped_session, sessionmaker

app = Flask(__name__)

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

DATABASE_URL = "postgres://zitohbxevdsjsq:4cfa033e54af2a9384e7894e046e88529476b882df9940e4256d3476eaf2daed@ec2-50-17-194-129.compute-1.amazonaws.com:5432/ddjjjq1o3b2sqg"

# Set up database
engine = create_engine(os.getenv("DATABASE_URL"))
db = scoped_session(sessionmaker(bind=engine))

@app.route("/register", methods=["GET", "POST"])
def register():

    if request.method == "GET":

        # Returns the registration page
        return render_template("register.html")

    else:

        # Processes the values sent by the form
        name = request.form.get("name")
        contact_number = "+91" + request.form.get("contact-number")
        email_address = request.form.get("email-address")
        roll_number = request.form.get("roll-number")
        coming = request.form.get("Radios")
        if name == None:
            return render_template("error.html", error="PLEASE ENTER YOUR NAME")
        elif contact_number == None:
            return render_template("error.html", error="PLEASE ENTER YOUR CONTACT NUMBER")
        elif email_address == None:
            return render_template("error.html", error="PLEASE ENTER YOUR EMAIL ADDRESS")
        elif roll_number == None:
            return render_template("error.html", error="PLEASE ENTER YOUR ROLL NUMBER")
        elif coming == None:
            return render_template("error.html", error="PLEASE ENTER WHETHER YOU ARE COMING OR NOT")

        # To check whether the user is already present or not
        rows = db.execute("SELECT * FROM people WHERE roll=:roll", {"roll":roll_number}).fetchall()
        if len(rows) == 1:
            return render_template("error.html", error="YOU HAVE ALREADY REGISTERED")

        # Inserts values into the database
        db.execute("INSERT INTO people (name, contact, email, roll, coming) VALUES (:name, :contact, :email, :roll, :coming)", {"name":name, "contact":contact_number, "email":email_address, "roll":roll_number, "coming": coming})

        # If they are coming then insert into another database
        if coming == "Yes":
            db.execute("INSERT INTO participants (name, contact, email, roll) VALUES (:name, :contact, :email, :roll)", {"name":name, "contact":contact_number, "email":email_address, "roll":roll_number})
        db.commit()

        # Returns the page on successful attempt
        return render_template("success.html")

@app.route("/")
def index():
    return render_template("index.html")
