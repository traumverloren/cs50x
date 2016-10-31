<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("edit_password.php", ["title" => "Update Password"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    
    { // validate submission
        if (empty($_POST["password"]))
        {
            apologize("You must provide a password.");
        }
        else if ($_POST["password"] != $_POST["password_confirmation"])
        {
            apologize("Sorry, your passwords didn't match. Try again.");
        }

        // update user's password
        $new_password = password_hash($_POST["password"], PASSWORD_DEFAULT);
        CS50::query("UPDATE users SET hash = '$new_password' WHERE id = ?", $_SESSION["id"]);

        // redirect to portfolio
        redirect("/");

    }
?>
