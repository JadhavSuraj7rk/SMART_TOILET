<?php
$timeA = '00:30:00';
$timeB = '14:00:00';
$interval = 30; // minutes
$inputTime = '00:45:00'; // user inputted time
$input = new DateTime($inputTime);
$begin = new DateTime($timeA);
$end = new DateTime($timeB);
if($input >= $begin && $input <= $end) {
    echo 'Success';
} else {
    echo 'Fail';
}
date_default_timezone_set("Asia/Kolkata");
$date1=date("h:i:s");
echo $date1;
?>