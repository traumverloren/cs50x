<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // query database for user's stocks
        $symbols = CS50::query("SELECT symbol FROM portfolios WHERE user_id = ?", $_SESSION["id"]);

        if ($symbols != false)
        {
            // render form
            render("sell.php", ["title" => "Sell", "symbols" => $symbols]);
        }
        else
        {
            apologize("Nothing to sell.");

        }
  }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must select a stock to sell.");
        }
        
        // lookup stock price
        $stock = lookup($_POST["symbol"]);
        $price = $stock['price'];

        // find the number of shares sold
        $shares = CS50::query("SELECT shares FROM portfolios WHERE symbol = ?", $_POST["symbol"]);
        $shares = $shares[0]["shares"];


        // calculate money owed from stock sale
        $profit = $shares * $price;
        
        // delete stock from user's portfolio
        CS50::query("DELETE FROM portfolios WHERE user_id = ? AND symbol =?", $_SESSION["id"], $_POST["symbol"]);
        
        // update user's cash balance after the sale
        CS50::query("UPDATE users SET cash = cash + $profit WHERE id = ?", $_SESSION["id"]);
        
        // create a record in history table
        CS50::query("INSERT INTO history (user_id, symbol, shares, price, transaction_type) VALUES(?, ?, ?, ?, ?)", $_SESSION["id"], strtoupper($_POST["symbol"]), $shares, $price, "SELL");

        // redirect to portfolio
        redirect("/");

    }

?>
