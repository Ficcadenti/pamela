<section id="parameter_root">
      <header class="header-sezione">
          <h2>Input parameters</h2>
      </header>
      <br><br>
</section>

<form method="POST" class="panel-carousel" id="eventForm">
    <p><span class="error">* Required information.</span></p>
    
    
    <!--
    <div class="form-group">
        <label for="InputName">Name png file</label><span class="error" style="color:red;font-weight:bold">*</span><span class="question"><p>Insert name of generated png file.</p></span>
        <input type="text" class="form-control" id="png" value="<?php echo $png;?>">
    </div>
    -->
    <div id="time_input">
      <input id="box1" type="checkbox"  data-toggle="collapse" data-target="#time">
      <label for="box1">Time (GMT)</label><span class="question"><p>Start Time.</p></span>

      <div id="time" class="row collapse">
        <div class="col-xs-6 col-sm-3">
              <label for="InputName">From</label>
              <input class="form-control" name="from" id="from"  placeholder="2010-06-03 00:00:00.0" type="text">
        </div>

        <div class="col-xs-6 col-sm-3">
            <label for="InputName">To</label>
            <input class="form-control" name="to" id="to"  placeholder="2010-06-03 00:00:00.0" type="text">
        </div>

        <div class="row">
          <div class="col-xs-2">
          <br>
            <p>Condition: <input class="cursoir_pointr" type="radio" value="AND" id="and1" name="condition1" checked><label for="and1">AND</label></p>
          </div>

          <div class="col-xs-2">
          <br>
            <p ><input type="radio" value="OR" id="or1" name="condition1" ><label for="or1">OR</label></p>
          </div>
        </div>
      </div>
    </div>

    <br>

    <div id="latitude_input">
      <input id="box2" type="checkbox" data-toggle="collapse" data-target="#latitude">
      <label for="box2">Latitude</label><span class="question"><p>Latitude range.</p></span>

      <div id="latitude" class="row collapse">
        <div class="col-xs-2 ">
              <label for="InputName">From</label>
              <input type="text" class="form-control" id="nameLat" value="">
              <br>
              <div id="slider-5"></div>
        </div>

        <div class="col-xs-2">
             <label for="InputName">To</label>
              <input type="text" class="form-control" id="name" value="">
        </div>

        <div class="row">
          <div class="col-xs-2">
          <br>
            <p>Condition: <input type="radio" value="AND" id="and" name="condition" checked><label for="and">AND</label></p>
          </div>

          <div class="col-xs-2">
          <br>
            <p ><input type="radio" value="OR" id="or" name="condition" ><label for="or">OR</label></p>
          </div>
        </div>

      </div>

    </div>

    <br>

    <div id="longitude_input">
      <input id="box3" type="checkbox" data-toggle="collapse" data-target="#longitude">
      <label for="box3">Longitude</label><span class="question"><p>Longitute range.</p></span>

      <div id="longitude" class="row collapse">
        <div class="col-xs-2">
              <label for="InputName">From</label>
              <input type="text" class="form-control" id="name" value="">
        </div>

        <div class="col-xs-2">
             <label for="InputName">To</label>
              <input type="text" class="form-control" id="name" value="">
        </div>

        <div class="row">
          <div class="col-xs-2">
          <br>
            <p>Condition: <input type="radio" value="AND" id="and2" name="condition2" checked><label for="and2">AND</label></p>
          </div>

          <div class="col-xs-2">
          <br>
            <p ><input type="radio" value="OR" id="or2" name="condition2" ><label for="or2">OR</label></p>
          </div>
        </div>
      </div>
    </div>

    <br>

    <div id="altitude_input" data-toggle="collapse" data-target="#altitude">
      <input id="box4" type="checkbox">
      <label for="box4">Altitude</label><span class="question"><p>Altitude range.</p></span>

      <div id="altitude" class="row collapse">
        <div class="col-xs-2">
              <label for="InputName">From</label>
              <input type="text" class="form-control" id="name" value="">
        </div>

        <div class="col-xs-2">
             <label for="InputName">To</label>
              <input type="text" class="form-control" id="name" value="">
        </div>
      </div>
    </div>

    <br>

    <div class="form-group">
        <label for="InputName">Output ROOT file</label><span class="error" style="color:red;font-weight:bold">*</span><span class="question"><p>Insert name of generated root file.</p></span>
        <input type="text" class="form-control" id="name" value="<?php echo $name;?>">
    </div>

    <br><br>

    <div class="row">
        <div class="col-xs-6 col-sm-3">
                  <button class="btn btn-info pull-right" type="button" onclick="lanciaQuery();">Run Query</button>
        </div>
        
        <div class="col-xs-6 col-sm-3"> 
                  <!-- <input type="submit" name="submit" value="Show root map" class="btn btn-info pull-right">  -->
                  <a href="components/drawroot.php?file=../dati/files/default.root&nobrowser&item=Histogram%20hnorm;1&opt=colz" target="_blank" class="btn btn-info pull-right">Show Root Map</a>
                  
        </div>
        
        <div class="col-xs-6 col-sm-3">
                  <!--<input type="submit" name="submit" value="Download Root File" class="btn btn-success pull-right">-->
                  <a href="./dati/files/default.root" class="btn btn-success pull-right">Download Root File</a>
        </div>
    </div>

</form>

<br><br><br><br><br>
                      