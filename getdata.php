<?php
//karena setiap inputan ajax berupa array post/get maka akan dicek indeks tiap array untuk tiap2 kasus fungsi ajax
if(isset($_POST)){
    if(isset($_POST['key'])){

          //untuk menginlcude koneksi dengan database 
          include "conn.php";

        
          if($_POST['key']=='getdataAx'){
            $hasilquery = mysqli_query($mysqli,"SELECT Ax FROM mpu6050 ORDER BY ID DESC LIMIT 1;");
            if(mysqli_num_rows($hasilquery)>0){
               $response = "";
               while($data  = mysqli_fetch_array($hasilquery)){
                  $response .= "".$data['Ax'];
                  exit($response);
               }
            }else{
                exit('nodata');
            }
          }elseif($_POST['key']=='getdataAy'){
            $hasilquery = mysqli_query($mysqli,"SELECT Ay FROM mpu6050 ORDER BY ID DESC LIMIT 1;");
            if(mysqli_num_rows($hasilquery)>0){
               $response = "";
               while($data = mysqli_fetch_array($hasilquery)){
                  $response .= "".$data['Ay'];
                  exit($response);
               }
            }else{
                exit('nodata');
            }
          }elseif($_POST['key']=='getdataAz'){
            $hasilquery = mysqli_query($mysqli,"SELECT Az FROM mpu6050 ORDER BY ID DESC LIMIT 1;");
            if(mysqli_num_rows($hasilquery)>0){
               $response = "";
               while($data = mysqli_fetch_array($hasilquery)){
                  $response .= "".$data['Az'];
                  exit($response);
               }
            }else{
                exit('nodata');
            }
          }elseif($_POST['key']=='getdataGx'){
            $hasilquery = mysqli_query($mysqli,"SELECT Gx FROM mpu6050 ORDER BY ID DESC LIMIT 1;");
            if(mysqli_num_rows($hasilquery)>0){
               $response = "";
               while($data = mysqli_fetch_array($hasilquery)){
                  $response .= "".$data['Gx'];
                  exit($response);
               }
            }else{
                exit('nodata');
            }
          }elseif($_POST['key']=='getdataGy'){
            $hasilquery = mysqli_query($mysqli,"SELECT Gy FROM mpu6050 ORDER BY ID DESC LIMIT 1;");
            if(mysqli_num_rows($hasilquery)>0){
               $response = "";
               while($data = mysqli_fetch_array($hasilquery)){
                  $response .= "".$data['Gy'];
                  exit($response);
               }
            }else{
                exit('nodata');
            }
          }elseif($_POST['key']=='getdataGz'){
            $hasilquery = mysqli_query($mysqli,"SELECT Gz FROM mpu6050 ORDER BY ID DESC LIMIT 1;");
            if(mysqli_num_rows($hasilquery)>0){
               $response = "";
               while($data = mysqli_fetch_array($hasilquery)){
                  $response .= "".$data['Gz'];
                  exit($response);
               }
            }else{
                exit('nodata');
            }
          }elseif($_POST['key']=='getdataLabel'){
            $hasilquery = mysqli_query($mysqli,"SELECT Label FROM mpu6050 ORDER BY ID DESC LIMIT 1;");
            if(mysqli_num_rows($hasilquery)>0){
               $response = "";
               while($data = mysqli_fetch_array($hasilquery)){
                  $response .= "".$data['Label'];
                  exit($response);
               }
            }else{
                exit('nodata');
            }
          }
    }
}    
?>