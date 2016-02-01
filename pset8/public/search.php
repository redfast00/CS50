<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];
    
    // Satanize (uh, sanitize) input
    if (empty($_GET["geo"]))
    {
        return false;
    }
    // http://stackoverflow.com/a/659030
    $geo = preg_replace("/[^A-Za-z0-9 ]/", '', $_GET["geo"]);
    
    // Check if input is a post code
    if (ctype_digit($geo))
    {
        $places = CS50::query("SELECT * FROM places WHERE postal_code LIKE ?", $geo . "%");
    }
    else
    {
        // Added config file in order to be able to search for text of 2 letters
        // http://cs50.stackexchange.com/q/15034
        $places = CS50::query("
            SELECT * FROM places WHERE MATCH(place_name, admin_name1, admin_code1) AGAINST (?)
            ", $geo);
    }
   
    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>