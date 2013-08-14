/**
 * @file
 * Javascript to display a popup after a delay.
 */

(function ($) {

Drupal.behaviors.initPopupAd = {
  attach: function (context, settings) {
    if (!$.isFunction($.colorbox)) {
      return;
    }

    $('body', context).once('popupad', function() {
      var popupad_settings = settings.popupad;

      setTimeout(function() {
        $.colorbox(popupad_settings);
      }, popupad_settings.delay);
    });
  }
}

})(jQuery);
