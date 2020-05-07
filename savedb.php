<?php

if(isset($_POST)){

  //untuk menginlcude koneksi dengan database
  include "conn.php";

  $Ax =  mysqli_escape_string($mysqli,$_POST['Ax']); 
  $Ay =  mysqli_escape_string($mysqli,$_POST['Ay']);
  $Az =  mysqli_escape_string($mysqli,$_POST['Az']);
  $Gx =  mysqli_escape_string($mysqli,$_POST['Gx']);
  $Gy =  mysqli_escape_string($mysqli,$_POST['Gy']);
  $Gz =  mysqli_escape_string($mysqli,$_POST['Gz']);

  $comm = "c:\Users\anoma\AppData\Local\Programs\Python\Python38-32\python.exe c:\xampp\htdocs\mqtt\mpu6050mqtts.py -x ".sprintf("%.2f", $Ax)." -y ".sprintf("%.2f", $Ay)." -z ".sprintf("%.2f", $Az)." -a ".sprintf("%.2f", $Gx)." -b ".sprintf("%.2f", $Gy)." -c ".sprintf("%.2f", $Gz);

  $label = shell_exec($comm); 
  
  $hasilquery = mysqli_query($mysqli,"INSERT INTO mpu6050(Ax,Ay,Az,Gx,Gy,Gz,Label) VALUES ($Ax,$Ay,$Az,$Gx,$Gy,$Gz,' ')");
  exit('Data Has Been Inserted');
}
 
?>
 