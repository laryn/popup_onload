/**
 * @file
 * Popup Onload js file.
 */

(function ($, window, Drupal) {
  'use strict';

  /**
   * Attaches the Popup Onload behaviour.
   */
  Drupal.behaviors.popupOnload = {
    attach: function (context, settings) {
      var _this = this;
      if (settings.popupOnload && !_this.popupInitialized) {
        var popupSettings = settings.popupOnload;
        setTimeout(function () {
          var $previewDialog = $('<div />').html(popupSettings.html).appendTo('body');
          Drupal.dialog($previewDialog, popupSettings).showModal();
          _this.popupInitialized = true;
        }, popupSettings.delay);
      }
    },
    popupInitialized: false
  };

})(jQuery, window, Drupal);
