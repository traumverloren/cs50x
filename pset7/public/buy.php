<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("buy_form.php", ["title" => "Buy"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must enter a stock symbol.");
        }
        else if (empty($_POST["shares"]))
        {
            apologize("You must specify the number of shares.");
        }
        else if (!preg_match("/^\d+$/", $_POST["shares"]))
        {
            apologize("Invalid number of shares.");
        }
        
        // query database for user's cash
        $cash = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        $cash = $cash[0]['cash'];

        // lookup stock price
        $stock = lookup($_POST["symbol"]);
        $price = $stock['price'];
        
        // calculate money needed for stock purchase
        $cost = $_POST["shares"] * $price;

        // check that user has cash to cover the cost of stock purchase
        if ($cost > $cash)
        {
            apologize("You don't have enough money for this purchase.");
        }
        
        // insert/combine shares to user's portfolio
        CS50::query("INSERT INTO portfolios (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], strtoupper($_POST["symbol"]), $_POST["shares"]);
    
        // deduct stock costs from user's cash
        CS50::query("UPDATE users SET cash = cash - $cost WHERE id = ?", $_SESSION["id"]);

        
        // redirect to portfolio
        redirect("/");

    }

?>
