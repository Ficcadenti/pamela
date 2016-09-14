<div class="container">
  <h2>Modal Example</h2>
  <!-- Trigger the modal with a button -->
  <button type="button" class="btn btn-info btn-lg" data-toggle="modal" data-target="#myModal">Open Modal</button>

  <!-- Modal -->
  <div class="modal fade" id="myModal" role="dialog">
    <div class="modal-dialog">
    
      <!-- Modal content-->
      <div class="modal-content">
        <div class="modal-header">
          <button type="button" class="close" data-dismiss="modal">&times;</button>
          <h4 class="modal-title">Modal Header</h4>
        </div>
        <div class="modal-body">
          <p>Some text in the modal.</p>
        </div>
        <div class="modal-footer">
          <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
        </div>
      </div>
      
    </div>
  </div>
  
</div>


<form>
    Numbers only:
    <input class="numeric" type="text" />
        <br/><br/>
    Integers only:
    <input class="integer" type="text" />
        <br/><br/>
    No negative values:
    <input class="positive" type="text" />
        <br/><br/>
    No negative values (integer only):
    <input class="positive-integer" type="text" />
        <br/><br/>
        Numbers with up to 2 decimal places:
    <input class="decimal-2-places" type="text" />
        <br/><br/>
    <a href="#" id="remove">Remove numeric</a>
</form>

<script type="text/javascript">
  $(".numeric").numeric();
  $(".integer").numeric(false, function() { alert("Integers only"); this.value = ""; this.focus(); });
  $(".positive").numeric({ negative: false }, function() { alert("No negative values"); this.value = ""; this.focus(); });
  $(".positive-integer").numeric({ decimal: false, negative: false }, function() { alert("Positive integers only"); this.value = ""; this.focus(); });
    $(".decimal-2-places").numeric({ decimalPlaces: 2 });
  $("#remove").click(
    function(e)
    {
      e.preventDefault();
      $(".numeric,.integer,.positive,.positive-integer,.decimal-2-places").removeNumeric();
    }
  );
  </script>