<?php

    // configuration
    $reward = 1000;
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("deposit_form.php", ["title" => "Deposit", "cash" => getCash(), "reward" => $reward]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $url = $_POST["url"];
        // validate submission
        if (empty($url))
        {
            apologize("You must provide a url");
        }
        else if (filter_var($url, FILTER_VALIDATE_URL) === false)
        {
            apologize("Invalid url");
        }
        // Not actually checking if url is an image of a cat for performance/security
        else
        {
            $valid = false;
            $image_ext = [".gif", ".jpg", ".jpeg", ".bmp", ".png"];
            foreach ($image_ext as $ext)
            {
                if (endsWith($url, $ext))
                {
                    $valid = true;
                    break;
                }
            }
            if (! $valid)
            {
                apologize("The URL must end with the extension of an image format");
            }
        }
        CS50::query("START TRANSACTION");
        CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $reward, $_SESSION["id"]);
        CS50::query("INSERT INTO cats (user_id,url) VALUES (?,?)",
                    $_SESSION["id"], $url);
        CS50::query("INSERT INTO history (price, symbol, user_id, shares) VALUES (?,'deposit',?,1)",
                    $reward, $_SESSION["id"]);
        CS50::query("COMMIT");
        redirect("/");
    }

?>