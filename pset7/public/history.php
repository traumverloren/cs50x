<?php

    // configuration
    require("../includes/config.php"); 

    // query database for user's history by using the user_id stored in the session.
    $rows = CS50::query("SELECT * FROM history WHERE user_id = ? ORDER BY created_at DESC;", $_SESSION["id"]);

    $positions = [];
    
    setlocale(LC_MONETARY, 'en_US.UTF-8');
    
    foreach ($rows as $row)
    {
        $positions[] = [
            "transaction_type" => $row["transaction_type"],
            "created_at" => $row["created_at"],
            "price" => money_format('%.2n', $row["price"]),
            "shares" => $row["shares"],
            "symbol" => strtoupper($row["symbol"])
        ];
    }
    

    // render history
    render("history.php", ["positions" => $positions, "title" => "History"]);

?>
