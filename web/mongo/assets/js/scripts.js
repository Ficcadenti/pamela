/*
**************************************************************************
  (c) Raffaele Ficcadenti 
  Maggio 2016
  raffaele.ficcadenti@gmail.com

  File: script.js
  Descr:    
************************************************************************** 
*/

/*$(function() {

    function toggleChevron(e) {
        $(e.target)
                .prev('.panel-heading')
                .find("i")
                .toggleClass('rotate-icon');
        $('.panel-body.animated').toggleClass('zoomIn zoomOut');
    }
    
    $('#accordion').on('hide.bs.collapse', toggleChevron);
    $('#accordion').on('show.bs.collapse', toggleChevron);

    var urlmenu = document.getElementById( 'selectLang' );
    
    urlmenu.onchange = function() 
    {
      window.open( this.options[ this.selectedIndex ].value , "_self");
    };

    $( "#slider-5" ).slider({
       orientation:"horizontal",
       min: -90,
      max: 90,
       slide: function( event, ui ) {
          $( "#latitude_min" ).val( ui.value );
       }  
    });
    $( "#latitude_min" ).val( $( "#slider-5" ).slider( "value" ) );


});*/


/* Validazione form */
$(document).ready(function(){
         

         // browser window scroll (in pixels) after which the "back to top" link is shown
          var offset = 300,
            //browser window scroll (in pixels) after which the "back to top" link opacity is reduced
            offset_opacity = 1200,
            //duration of the top scrolling animation (in ms)
            scroll_top_duration = 600,
            //grab the "back to top" link
            $back_to_top = $('.cd-top');

          //hide or show the "back to top" link
          $(window).scroll(function(){
            ( $(this).scrollTop() > offset ) ? $back_to_top.addClass('cd-is-visible') : $back_to_top.removeClass('cd-is-visible cd-fade-out');
            if( $(this).scrollTop() > offset_opacity ) 
            { 
                $back_to_top.addClass('cd-fade-out');
            }

            if ($(window).scrollTop() > 50)
            {
                $('.navbar-default').css('background','rgb(255, 255, 255)').stop().animate({"opacity":".8"},100)
            }
            else if ($(window).scrollTop() < 50)
            {
                $('.navbar-default').css('background','rgb(255, 255, 255)').stop().animate({"opacity":"1"},100)
            }

          });

          //smooth scroll to top
          $back_to_top.on('click', function(event){
            event.preventDefault();
            $('body,html').animate({
              scrollTop: 0 ,
              }, scroll_top_duration
            );
          });

          /*$('#op2').on('change', function() {
            if(this.value!="none")
            {

              $('#op3').prop('disabled', false);
              $('#time_max').prop('disabled', false);
              $('#op4').prop('disabled', false);
            }else
            {
              $('#op3').prop('disabled', true);
              $('#time_max').prop('disabled', true);
              $('#op4').prop('disabled', true);
            }
          });*/

}); 

function showRoot()
{
      var root_file=$("select[id='listRootFile']").val();
      if(root_file==="") /* da cambiare con if file exists */
      {
          alert("Insert Output ROOT file!!!!");
      }
      else
      {
          window.open("components/drawroot.php?file=../dati/files/"+root_file+"&nobrowser&item=Histogram%20hnorm;1&opt=colz","_blank");
      }
};

function downloadRoot()
{
      var root_file=$("select[id='listRootFile']").val();
      if(root_file==="")  /* da cambiare con if file exists */
      {
          alert("Insert Output ROOT file!!!!")
      }
      else
      {
          location.href="./dati/files/"+root_file;
      }
};


function deleteRoot()
{
      var root_file=$("select[id='listRootFile']").val();
      alert(root_file);
      $("#rotFileDelete").text("Delete '"+root_file+"'");

      if(root_file==="")  /* da cambiare con if file exists */
      {
          alert("Insert Output ROOT file!!!!")
      }
      else
      {
          /* cancella file */
      }
};

    function getStatus()
    {
          alert("getStatus");
          var ajax = assegnaXMLHttpRequest();
          var data_post= "";

          if(ajax) 
            {
             // chiamata AJAX
             $.ajax({
               url: 'components/getstatus.php',
               type: 'POST',
               data: data_post,
               success: function(res)
               {
                  var value = JSON.parse(res);
                  if(value.status==2)
                  {
                    // $("#btnShow").removeClass("disabled");
                    // $("#btnDownload").removeClass("disabled");

                    $("#loading").fadeOut(800,function()
                     {
                       $("#loading").remove();
                     });

                    $("#regok").fadeOut(800,function()
                     {
                       $("#regok").remove();
                     });

                    stopGetStatus();
                  }
                  else
                  {
                    // $("#btnShow").addClass("disabled");
                    //$("#btnDownload").addClass("disabled");
                  }
               }
             });
            }

    };

    var myInterval;
    var root_file_in_query;

    function setStatusInterval()
    {
        alert("setStatusInterval");
        myInterval=setInterval(getStatus, 5000);
    };


    function stopGetStatus() 
    {
        clearInterval(myInterval);
        alert("The root file was generated");
        //$("#listRootFile").append("<option>"+root_file_in_query+"</option>");
        /* Reload dir ../dati/files/ */
    };

    function lanciaQuery()
    {
        var $tab = $('#myTabContent'), $active = $tab.find('.tab-pane.active'), text = $active.find('#tabSelect').text();
        

        var root_file=$("input[id='root_file']").val();
        root_file_in_query=root_file;

        var mongo_query=$("textarea[id='mongoQuery']").val();
        var tab_select=0;

        var flag=0;


        if(root_file==="") /* variabile comune */
        {
            alert("Insert Output ROOT file!!!!")
            flag=1;
        }

        if(text==="beginner") /* Modalita semplificata */
        {
              tab_select=0;
        }
        else if(text==="expert") /* Modalità esperta, l'utente inserisce la query mongo */
        {

            if(mongo_query==="")
            {
                alert("Insert Mongo Query!!!!")
                flag=1;
            }
            tab_select=1;
        }

        if(flag==0)
        {
            $("#regok").remove();
            $("#exec_query").append('<img src="media/loading.gif" alt="loading" id="loading" >');

            var ajax = assegnaXMLHttpRequest();
            var data_post= "";

            if(tab_select==0) /* Modalita semplificata */
            {
                data_post=  "root_file="+root_file+
                        "&tab_select="+tab_select;
            }
            else /* Modalità esperta, l'utente inserisce la query mongo */
            {
                data_post=  "root_file="+root_file+
                        "&tab_select="+tab_select+
                        "&mongo_query="+mongo_query;                    
            }

            if(ajax) 
            {
             // chiamata AJAX
             $.ajax({
               url: 'components/pamelamongodev.php',
               type: 'POST',
               data: data_post,
               success: function(res)
               {
                 /*$("#loading").fadeOut(800,function()
                 {
                   $("#loading").remove();
                   $("#exec_query").append('<p id="regok">'+res+'</p>');
                 });*/
                 $("#exec_query").append('<p id="regok">'+res+'</p>');
               }
             });
            }
         }

    }

    /*$(document).ready(function(){
      $('a[data-toggle="tab"]').on('shown.bs.tab', function(e){
          var currentTab = $(e.target).text(); // get current tab
         alert(currentTab);
      });
    });*/
