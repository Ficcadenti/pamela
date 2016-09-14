<section id="parameter_root">
      <header class="header-sezione">
          <h2>PROVA</h2>
      </header>
      <br><br>
</section>


 <form class="form-inline panel-carousel" role="form">
    <p><span class="error">* Required information.</span></p>
  

    <br>

    <div id="latitude_input">
      <script type="text/javascript">
          function getval(sel) 
          {
             alert(sel.value);
             if(sel.value!="none")
              {

                $("#op3").prop("disabled", false);
                $("#latitude_max").prop("disabled", false);
                $("#slider-6").prop("disabled", false);
              }else
              {
                $("#op3").prop("disabled", true);
                $("#latitude_max").prop("disabled", true);
                $("#slider-6").prop("disabled", false);
              }
          };
          
          $(function() {
              $( "#slider-6" ).slider(
                {
                      orientation:"horizontal",
                      min: -90,
                      max: 90,
                      slide: function( event, ui ) {
                      $( "#latitude_max" ).val( ui.value );
                }  
              });

              $( "#latitude_max" ).val( $( "#slider-6" ).slider( "value" ) );
              
              $("#slider-6").prop("disabled", true);

          });

      </script>
      <input id="box2" type="checkbox"  data-toggle="collapse" data-target="#latitude">
      <label for="box2">Latitude</label><span class="question"><p>Enter the latitude intervals with any conditions,<br>Latitudes range from -90 to 90.</p></span>

      <div id="latitude" class="collapse">
              <?php include("components/option1.php") ?>
              <div class="form-group">
                <input type="text" class="form-control col-xs-2" id="latitude_min"  maxlength="3" size="3" value="0">
              </div>
              <div class="form-group" id="slider-5" style="width:100px;margin-right:20px;margin-left:5px"></div>

              <?php include("components/option2.php") ?>

              <?php include("components/option3.php") ?>
              <div class="form-group">
                <input type="text" class="form-control" id="latitude_max"  maxlength="3" size="3" value="0" disabled>
              </div>
              <div class="form-group" id="slider-6" style="width:100px;margin-right:20px;margin-left:5px" disabled>
              </div>

              <?php include("components/option4.php") ?>
      </div>
    </div>

  </form>



<br><br><br><br><br>
                      