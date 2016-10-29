<?php

    // configuration
    require("../includes/config.php"); 

    // query database for user's portfolio by using the user_id stored in the session.
    $rows = CS50::query("SELECT * FROM portfolios WHERE user_id = ?", $_SESSION["id"]);

    // query database for user's cash balance by using the id stored in the session.
    $balance = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    $balance = $balance[0]["cash"];

    $positions = [];
    
    setlocale(LC_MONETARY, 'en_US.UTF-8');
    
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => money_format('%.2n', $stock["price"]),
                "shares" => $row["shares"],
                "symbol" => strtoupper($row["symbol"])
            ];
        }
    }
    

    // render portfolio
    render("portfolio.php", ["positions" => $positions, "balance" => $balance, "title" => "Portfolio"]);

?>
