<?php

    require(__DIR__ . "/../includes/config.php");

    $query = preg_split("/[\s,+]+/", $_GET["geo"]);
    
    // if it's a zip code, set the search_string as only the zip code
    if (is_numeric($query[0]))
    {
        $search_string = $query[0];
    }
    
    // for all other instances, stitch together for the fulltext search
    else
    {
        $query = preg_filter('/^/', '+', $query);
        $search_string = implode(" ", $query);
    }
    
    // numerically indexed array of places
    $places = [];

    // search database for places matching $_GET["geo"], store in $places
    $rows = CS50::query("SELECT * FROM places WHERE postal_code = ? OR
                            MATCH (place_name, admin_name1) AGAINST (? IN BOOLEAN MODE)", $search_string, $search_string);
    foreach ($rows as $row)
    {
        $places[] = [
            "id" => $row["id"],
            "country_code" => $row["country_code"],
            "postal_code" => $row["postal_code"],
            "place_name" => $row["place_name"],
            "admin_name1" => $row["admin_name1"],
            "admin_code1" => $row["admin_code1"],
            "admin_name2" => $row["admin_name2"],
            "admin_code2" => $row["admin_code2"],
            "admin_name3" => $row["admin_name3"],
            "admin_code3" => $row["admin_code3"],
            "latitude" => $row["latitude"],
            "longitude" => $row["longitude"],
            "accuracy" => $row["accuracy"],
        ];
    }

    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>