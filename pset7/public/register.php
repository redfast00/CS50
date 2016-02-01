<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // Check if valid register (username is not empty and passwords match)
        if (empty($_POST["username"]))
        {
            apologize("Username must not be empty");
        }
        else if (empty($_POST["password"]) || empty($_POST["confirmation"]))
        {
            apologize("Password must not be empty");
        }
        else if ($_POST["password"] !== $_POST["confirmation"])
        {
            apologize("Password and confirmation must be the same");
        }
        $r = CS50::query(
            "INSERT IGNORE INTO users (username, hash, cash)
            VALUES(?, ?, 10000.0000)", 
            $_POST["username"], 
            password_hash($_POST["password"], PASSWORD_DEFAULT)
        );
        if ($r === 0)
        {
            apologize("Username is taken, please use a different username");
        }
        $rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
        $_SESSION['id'] = $rows[0]["id"];
        redirect("/");
    }

?>

