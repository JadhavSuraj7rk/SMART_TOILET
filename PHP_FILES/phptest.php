<!DOCTYPE html>
<html lang="
" dir="ltr">
  <head>
    <meta charset="utf-8">
    <title></title>
  </head>
  <body>
    <form action="phptest.php" method="post">
      Name=<input type="text" name="name">
      <br>
      City=<input type="text" name="city">
      <br>
      Percentile=<input type="number" name="percentile">
      <br>
      <input type="submit">
    </form>
    <?php
     $servername="localhost";
     $user="root";
     $password="";
     $dbname = "test_database";
     $conn=mysqli_connect($servername,$user,$password,$dbname);
     $name= mysqli_real_escape_string($conn,$_POST["name"]);
     $city= mysqli_real_escape_string($conn,$_POST["city"]);
     $percentile= mysqli_real_escape_string($conn,$_POST["percentile"]);
     if(!$conn)
     {
       die("failed to connect".mysqli_connect_error());
     }
     else {
       echo "connected successfully <br>";
     }
     $query="INSERT INTO students (name,city,percentile) VALUES ('$name','$city','$percentile')";
     if (isset($name)){
     $fired=mysqli_query($conn, $query);}
     if ($fired) {
     echo "New record created successfully";
     }
     else{
     echo "Error: ".$query."<br>".mysqli_error($conn);
     }

     mysqli_close($conn);
    ?>
  </body>
</html>
