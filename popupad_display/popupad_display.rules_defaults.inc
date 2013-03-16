<?php
/**
 * @file
 * popupad_display.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function popupad_display_default_rules_configuration() {
  $items = array();
  $items['rules_display_popupad'] = entity_import('rules_config', '{ "rules_display_popupad" : {
      "LABEL" : "Display a popup ad",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "popupad" ],
      "ON" : [ "popupad_event_choose_popup" ],
      "IF" : [ { "popupad_condition_check_cookie" : { "popupad" : [ "popupad" ] } } ],
      "DO" : [ { "popupad_action_display_popup" : { "popupad" : [ "popupad" ] } } ]
    }
  }');
  return $items;
}
