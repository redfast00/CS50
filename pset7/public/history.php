<?php

    // configuration
    require("../includes/config.php"); 
    
    $rows = CS50::query("SELECT price, symbol, shares, timestamp FROM history WHERE user_id = ? ORDER BY timestamp", $_SESSION["id"]);
    if (count($rows) === 0)
    {
        apologize("You don't have any history");
    }
    $positions = [];
    foreach ($rows as $row)
    {
        $positions[] = [
            "timestamp" => $row["timestamp"],
            "price" => $row["price"],
            "shares" => abs($row["shares"]),
            "symbol" => $row["symbol"],
            "total" => $row["price"] * $row["shares"]
        ];
    }
    render("history_view.php", ["positions" => $positions, "title" => "History", "cash" => getCash()]);
?>
