<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("quote_form.php", ["title" => "Quote"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $symbol = strtoupper($_POST["symbol"]);
        // Check if valid register (username is not empty and passwords match)
        if (empty($_POST["symbol"]))
        {
            apologize("Stock symbol must not be empty");
        }
        $stock = lookup($symbol);
        if ($stock === false)
        {
            apologize("Ensure stock exists");
        }
        $price = number_format($stock["price"], 2, '.', '');
        $name = $stock["name"];
        render("quote_view.php", ["price" => $price, "name" => $name, "symbol" => $symbol]);
    }

?>