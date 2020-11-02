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
  
 
?>