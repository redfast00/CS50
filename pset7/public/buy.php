<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("buy_form.php", ["title" => "Buy", "cash" => getCash()]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $symbol = strtoupper($_POST["symbol"]);
        // validate submission
        if (empty($symbol))
        {
            apologize("You must provide a symbol of a stock to sell");
        }
        else if (! ctype_alnum($symbol))
        {
            apologize("Stock symbols only contain alphanumeric characters");
        }
        else if (empty($_POST["shares"]))
        {
            apologize("You must provide a number of shares");
        }
        else if (! ctype_digit($_POST["shares"]))
        {
            apologize("You must provide a valid integer");
        }
        $shares = (int) $_POST["shares"];
        $stock = lookup($symbol);
        if ($stock === false)
        {
            apologize("Invalid symbol");
        }
        $cost = $stock["price"] * $shares;
        $cash = getCash();
        if ($cash - $cost < 0)
        {
            apologize("Insufficient funds");
        }
        CS50::query("START TRANSACTION");
        CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $cost, $_SESSION["id"]);
        CS50::query("INSERT INTO portfolios (user_id,symbol,shares) VALUES (?,?,?) ON DUPLICATE KEY UPDATE shares=shares+?",
                    $_SESSION["id"], $symbol, $shares, $shares);
        CS50::query("INSERT INTO history (price, symbol, user_id, shares) VALUES (?,?,?,?)",
                    $stock["price"], $symbol, $_SESSION["id"], -$shares);
        CS50::query("COMMIT");
        redirect("/");
    }

?>