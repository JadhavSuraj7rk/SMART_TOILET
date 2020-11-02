<?php
 $servername="localhost";
 $user="root";
 $password="";
 $dbname = "toilet";
 $conn=mysqli_connect($servername,$user,$password,$dbname);

 if(!$conn)
 {
  die("failed to connect".mysqli_connect_error());
 }
 else {
  echo "connected successfully <br>";
 }
  $TOILET_ID=$_GET['ToCo_id'];
  $AIR_QUALITY=$_GET['gas'];
  $COUNT=$_GET['count1'];
  $WATER=$_GET['water'];
  $DIRT=$_GET['dirty'];
  $AREA=$_GET['area'];
  $COMPARTMENT=$_GET['compartment'];
  $sql="INSERT INTO station1(TOILET_ID, AIR_QUALITY, COUNT, DIRT, WATER, AREA, COMPARTMENT) VALUES ('$TOILET_ID','$AIR_QUALITY','$COUNT','$DIRT','$WATER','$AREA','$COMPARTMENT')";
  if(mysqli_query($conn, $sql)){
      echo "inserted";
  }
  else{
    echo "Error: " . $sql . "<br>" . mysqli_error($conn);
  }
 if($AIR_QUALITY>800||$DIRT=="YES"||$WATER=="NO") {
    $url="http://sms.swapneal.co.in/app/smsapi/index.php";
    // init the resource
 $ch = curl_init($url);
 curl_setopt_array($ch, array(
    CURLOPT_URL => $url,
    CURLOPT_RETURNTRANSFER => true,
    CURLOPT_POST => true,
    CURLOPT_POSTFIELDS => "key=25E17262B63CBD&routeid=415&type=text&contacts=7045310107&senderid=TEXTSM&msg=Please+Toilet+dho+lo"
    //,CURLOPT_FOLLOWLOCATION => true
 ));
 //http://sms.swapneal.co.in/app/smsapi/index.php?key=25E17262B63CBD&routeid=415&type=text&contacts=&senderid=TEXTSM&msg=Hello+People%2C+have+a+great+day

 //Ignore SSL certificate verification
 curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, 0);
 curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 0);


 //get response
 $output = curl_exec($ch);

 //Print error if any
 if(curl_errno($ch))
 {
    echo 'error:' . curl_error($ch);
 }
 else
 {
    echo 'Your msg has been sent '.$output;
 }
 curl_close($ch);



 }
 
?>