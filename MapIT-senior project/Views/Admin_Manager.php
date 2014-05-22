<?php
if (!isset($_SESSION)) {
    session_start();
}
ob_start();

//redirects back to main page in case there is no user
if (!isset($_SESSION['userid']) || $_SESSION['userid'] < 0) {
    header('Location: http://www.mocivilwar.org');
}

date_default_timezone_set('UTC');
?>

<!doctype html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <script src="../libraries/jquery-1.11.0.js"></script>
        <link rel="stylesheet" href="../libraries/jquery-ui-1.9.2.custom/css/redmond/jquery-ui-1.9.2.custom.css" />
        <script src="../libraries/jquery-ui-1.9.2.custom/js/jquery-ui-1.9.2.custom.js"></script>
        <script src="../libraries/jquery-ui-1.9.2.custom/js/jquery-ui-1.9.2.custom.min.js"></script>
        <script src="https://maps.googleapis.com/maps/api/js?key=AIzaSyBaB26c-fzIJpvh_zOm9ZINErBOOPQK078&sensor=false"></script>

        <link rel="stylesheet" href="../libraries/css/primary.css" />
        <link rel="stylesheet" href="../libraries/css/map.css" />

        <title>MapIT - Admin Manager</title>

        <script>
            $(document).ready(function() {
                //setup accordion
                $('#accordion').accordion({
                    icons: false
                });

                $('#users_btn').button({
                    icons: {
                        primary: "ui-icon-custom_user"
                    },
                    text: false
                }).click(function() { 
                    if ($('#userstatus').text() != 2) {
                        $('#dialog').dialog({
                            title: 'Notice',
                            buttons: [{
                                    text: 'OK',
                                    click: function() {
                                        $(this).dialog('close');
                                    }
                                }]
                        }).html('User dont have access to this area. Please, contact administrator.');
                    } else {
                        window.location = "../Controllers/User_Controller.php";
                    }
                });

                $('#dig_sites_btn').button({
                    icons: {
                        primary: "ui-icon-custom_cannon"
                    },
                    text: false
                }).click(function() {
                    if ($('#userstatus').text() != 2) {
                        $('#dialog').dialog({
                            title: 'Notice',
                            buttons: [{
                                    text: 'OK',
                                    click: function() {
                                        $