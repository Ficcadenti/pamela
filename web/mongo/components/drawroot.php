<!-- 
**************************************************************************
  (c) Raffaele Ficcadenti 
  Maggio 2016
  raffaele.ficcadenti@gmail.com

  File:   drawroot.php
  Descr:  Classe template per home page. Include le varie sezioni.
************************************************************************** 
-->
<!DOCTYPE html>
<!--[if IE 8]><html class="no-js lt-ie9" lang="en" ><![endif]-->
<!--[if gt IE 8]><!--><html class="no-js" ><!--<![endif]-->
<html lang="it">

 <head>
  <meta charset="utf-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Read a ROOT file</title>
  
  <!-- load stylesheet -->
  <?php
      $from_page="components";
      include ("../components/stylesheet.php");
      # Recupero il valore di lang
      if (isset($_GET['lang'])) 
      {
          $lang = $_GET['lang'];
          # Se la variabile lang è nulla viene selezionata di default
          # la lingua italiana (it)
          if ($lang == FALSE)
          {
              $lang = "it";
          }
      }
      else
      {
          $lang = "it";
      }
      # Includo il file di linguaggio interessato
      require("../components/linguaggio/{$lang}.php");
  ?>

  <!-- respond.js per IE8 -->
  <!--[if lt IE 9]>
  <script src="js/respond.min.js"></script>
  <![endif]-->


 </head>

 <body class="main">
    
    <!-- header (navigation bar & menu) -->
    <?php
      include("../components/header.php");
    ?>  

    <div class="container">

        <section id="parameter_root">
              <header class="header-sezione">
                  <h2>ROOT File</h2>
              </header>
              <br><br>
        </section>
 
        <div id="simpleGUI" class="panel-carousel centrato" >
        </div>
    
    </div>

    <!-- header (navigation bar & menu) -->
    <?php
      include("../components/footer.php");
    ?> 

    <!-- load scripts -->
    <?php
      $from_page="components";
      include ("../components/scripts.php");
    ?>  

    <script type="text/javascript" src="../assets/jsroot/scripts/JSRootCore.js?gui"></script>

    <!-- go to top -->
    <a href="#0" class="cd-top">Top</a>
 </body>

</html>
