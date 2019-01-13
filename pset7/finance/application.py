import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime
from pytz import timezone

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

# Initializing rows
rows = [[0 for x in range(500)] for y in range(500)]

# Initializing symbol
symbol = "DEFA"

# Initializing stock
stock = {"name": "DEFA", "price": 00.00, "symbol": "DEFA"}

# Initializing time
time = datetime.now(timezone('Asia/Kolkata'))


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Gets the number of stocks
    st = db.execute("SELECT * FROM buy WHERE id = :id", id=session["user_id"])

    price = []
    value = 0
    total = []

    for stocks in st:
        temp = lookup(stocks["symbol"])
        value = value + (temp["price"] * stocks["number"])
        price.append(temp["price"])
        total.append(usd(temp["price"] * stocks["number"]))

    for p in range(len(price)):
        price[p] = usd(price[p])

    # Gets the cash
    cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
    value = value + cash[0]["cash"]

    return render_template("index.html", stocks=st, cash=usd(cash[0]["cash"]), total=total, price=price, value=usd(value))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        global symbol
        symbol = request.form.get("symbol")

        # Ensure symbol was submitted
        if not symbol:
            return apology("must provide symbol", 400)

        # Ensure correct symbol is provided
        if not lookup(symbol):
            return apology("must provide proper symbol", 400)

        numbert = request.form.get("shares", type=int)

        # Ensure number was of proper format
        if not numbert:
            return apology("must provide a positive integer", 400)

        if not numbert >= 1:
            return apology("must provide a positive integer", 400)

        # Gets the stock details
        global stock
        stock = lookup(symbol)

        # Calculates the total price
        total = stock["price"] * numbert

        stock["price"] = usd(stock["price"])

        # Gets the cash
        cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])

        # Check whether there is enough cash
        if total > cash[0]["cash"]:
            return apology("not enough cash", 400)

        # Check whether stocks of the same company has been bought or not and proceed accordingly
        global rows
        rows = db.execute("SELECT * FROM Buy WHERE symbol = :symbol", symbol=stock["symbol"])

        number = db.execute("SELECT number FROM Buy WHERE symbol = :symbol", symbol=stock["symbol"])

        if not len(rows) == 0:
            # UPDATE TABLE "Buy"
            db.execute("UPDATE Buy SET number = :number WHERE symbol = :symbol",
                       number=number[0]["number"] + numbert, symbol=stock["symbol"])

        else:
            # INSERT into TABLE "Buy"
            db.execute("INSERT INTO Buy ('id', 'symbol', 'number', 'name') VALUES (:id, :symbol, :number, :name)",
                       id=session["user_id"], symbol=stock["symbol"], number=numbert, name=stock["name"])

        # Update TABLE "History"
        db.execute("INSERT INTO History ('id', 'symbol', 'status', 'p_bought', 'number') VALUES (:id, :symbol, :status, :p_bought, :number)",
                   id=session["user_id"], symbol=stock["symbol"], status="BUY", p_bought=stock["price"],
                   number=numbert)
        # UPDATE cash
        db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash=cash[0]["cash"] - total, id=session["user_id"])

        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Gets the number of transactions
    trans = db.execute("SELECT * FROM history WHERE id = :id ORDER BY time desc", id=session["user_id"])
    return render_template("history.html", transactions=trans)


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
        global rows
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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
    """Get stock quote."""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        global symbol
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("stock does not exist", 400)

        # Gets the stock details
        global stock
        stock = lookup(symbol)

        # Ensure the symbol typed by the user is valid
        if stock == None:
            return apology("symbol does not exist", 400)

        stock["price"] = usd(stock["price"])

        # Redirect user to quoted page
        return render_template("quoted.html", stock=stock)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
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

        # Ensure password was submitted
        elif not request.form.get("confirmation"):
            return apology("must confirm password", 400)

        # Ensure passwords match
        elif not request.form.get("confirmation") == request.form.get("password"):
            return apology("passwords do not match", 400)

        # Query database for username
        global rows
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Check whether the username already exits
        if len(rows) == 1:
            return apology("username already exists please login", 400)

        # Generate hash
        hash = generate_password_hash(request.form.get("password"))

        # INSERT into TABLE "users"
        db.execute("INSERT INTO users ('username', 'hash') VALUES (:username, :hash)",
                   username=request.form.get("username"), hash=hash)

        # Redirect to LOGIN page
        return redirect("/login")

    #  reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        global symbol
        symbol = request.form.get("symbol")

        # Ensure symbol was submitted
        if not symbol:
            return apology("must provide symbol", 400)

        # Ensure correct symbol is provided
        if not lookup(symbol):
            return apology("must provide proper symbol", 400)

        numbert = request.form.get("shares", type=int)

        # Gets the stock details
        global stock
        stock = lookup(symbol)
        number_stock = db.execute("SELECT number FROM Buy WHERE symbol = :symbol AND id = :id",
                                  symbol=symbol, id=session["user_id"])

       # Ensure number was of proper format
        if not numbert:
            return apology("must provide a valid number", 400)

        if numbert > number_stock[0]["number"]:
            return apology("must provide a valid number", 400)

        # Gets the cash
        cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])

        # Calculates the total price
        total = stock["price"] * numbert

        # Check whether stocks of the same company has been bought or not and proceed accordingly
        global rows
        rows = db.execute("SELECT * FROM Buy WHERE symbol = :symbol", symbol=stock["symbol"])

        number = db.execute("SELECT number FROM Buy WHERE symbol = :symbol", symbol=stock["symbol"])

        if not len(rows) == 0:

            # UPDATE TABLE "Buy"
            db.execute("UPDATE Buy SET number = :number WHERE symbol = :symbol",
                       number=number[0]["number"] - numbert, symbol=stock["symbol"])
            numberp = db.execute("SELECT number FROM Buy WHERE symbol = :symbol", symbol=stock["symbol"])
            if numberp[0]["number"] == 0:
                db.execute("DELETE FROM Buy WHERE symbol = :symbol", symbol=stock["symbol"])
            stock["price"] = usd(stock["price"])

            # UPDATE TABLE "History"
            db.execute("INSERT INTO History ('id', 'symbol', 'status', 'p_sold', 'number') VALUES (:id, :symbol, :status, :p_sold, :number)",
                       id=session["user_id"], symbol=stock["symbol"], status="SELL", p_sold=stock["price"],
                       number=numbert)
        else:
            return apology("stock not bought", 400)

        # UPDATE cash
        db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash=cash[0]["cash"] + total, id=session["user_id"])

        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        stocks = db.execute("SELECT symbol FROM Buy WHERE id = :id", id=session["user_id"])
        return render_template("sell.html", stocks=stocks)


@app.route("/cash", methods=["GET", "POST"])
@login_required
def cash():
    if request.method == "POST":
        add = request.form.get("cash", type=float)

        # Gets the cash
        cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])

        # UPDATE cash
        db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash=cash[0]["cash"] + add, id=session["user_id"])

        # UPDATE TABLE "History"
        db.execute("INSERT INTO History ('id', 'symbol', 'status', 'p_bought') VALUES (:id, :symbol, :status, :p_bought)",
                   id=session["user_id"], symbol="CASH", status="ADD", p_bought=usd(add))

        return render_template("cash_added.html", add=add)
    else:
        return render_template("cash.html")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
