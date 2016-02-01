<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        $rows = CS50::query("SELECT symbol FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
        if (count($rows) === 0)
        {
            apologize("You have nothing to sell");
        }
        render("sell_form.php", ["title" => "Sell", "symbols" => $rows]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        $symbol = strtoupper($_POST["symbol"]);
        if (empty($symbol))
        {
            apologize("You must provide a symbol of a stock to sell");
        }
        
        $sharess = CS50::query("SELECT shares FROM portfolios WHERE user_id = ? AND symbol = ?",
                              $_SESSION["id"], $symbol);
        if (count($sharess) !== 1)
        {
            apologize("You don't even own that stock, stop messin' with me");
        }
        $shares = $sharess[0]["shares"];
        $stock = lookup($_POST["symbol"]);
        if ($stock === false)
        {
            apologize("Invalid symbol");
        }
        $cost = $stock["price"] * $shares;
        $cash = getCash();
        CS50::query("START TRANSACTION");
        CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $cost, $_SESSION["id"]);
        CS50::query("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $symbol);
        CS50::query("INSERT INTO history (price, symbol, user_id, shares) VALUES (?,?,?,?)",
                    $stock["price"], $symbol, $_SESSION["id"], $shares);
        CS50::query("COMMIT");
        redirect("/");
    }

?>