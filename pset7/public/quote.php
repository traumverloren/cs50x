<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("quote.php", ["title" => "Get Quote"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a stock symbol.");
        }

        // look up a stock’s latest price
        $stock = lookup($_POST["symbol"]);

        // if symbol not found, apologize
        if ($stock == false)
        {
            apologize("Invalid stock symbol. Try again.");
          }

        // else render the stock quote
        render("show_quote.php", ["title" => "Latest Quote", "symbol" => $stock['symbol'], "name" => $stock['name'], "price" => $stock['price']]);
    }

?>
