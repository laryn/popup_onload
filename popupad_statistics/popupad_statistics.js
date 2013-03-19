/**
 * @file
 * Attach clicks/views statistics JS to colorbox.
 */

(function ($) {

Drupal.behaviors.attachPopupAdStatistics = {

  attach: function (context, settings) {
    if (!$.isFunction($.colorbox)) {
        return;
      }

    function PopupAdStatisticsLogAction(atype) {
      var popupad_settings = settings.popupad;

      $.ajax({
        async: false,
        dataType: 'json',
        data: {
          atype: atype,
          popup_id: popupad_settings.popup_id
        },
        type: 'POST',
        url: '/popupad_stats_log'
      });
    }

    $(document).bind('cbox_complete', function() {
      PopupAdStatisticsLogAction('view');

      $('#colorbox.popupad a, #colorbox.popupad area').click(function (event) {
        PopupAdStatisticsLogAction('click');
        return true;
      });
      $('#colorbox.popupad form').submit(function (event) {
        PopupAdStatisticsLogAction('click');
        return true;
      });
    });
  }
}

})(jQuery);
