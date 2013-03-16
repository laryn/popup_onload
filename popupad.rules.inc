<?php

/**
 * Implements hook_rules_event_info().
 */
function popupad_rules_event_info() {
  return array(
    'popupad_event_choose_popup' => array(
      'label' => t('There is a popup to display'),
      'group' => t('Popup Ad'),
      'variables' => array(
        'popupad' => array(
          'label' => t('popup ad entity'),
          'type' => 'popupad',
          'access callback' => 'popupad_integration_access',
        ),
      ),
    ),
  );
}

/**
 * Implements hook_rules_condition_info().
 */
function popupad_rules_condition_info() {
  return array(
    'popupad_condition_check_cookie' => array(
      'label' => t('Popup advertisement cookie is not set'),
      'parameter' => array(
        'popupad' => array(
          'type' => 'popupad',
          'label' => t('Popup ad entity'),
        ),
      ),
      'group' => t('Popup Ad'),
    ),
  );
}

/**
 * Implements hook_rules_action_info().
 */
function popupad_rules_action_info() {
  return array(
    'popupad_action_display_popup' => array(
      'label' => t('Display a popup'),
      'parameter' => array(
        'popupad' => array(
          'type' => 'popupad',
          'label' => t('Popup advertisement'),
        ),
      ),
      'group' => t('Popup Ad'),
    ),
  );
}

/**
 * Condition to check if popup cookie is set.
 */
function popupad_condition_check_cookie($popupad, $context = array()) {
  return !popupad_check_time_cookie($popupad, $context = array());
}

/**
 * Action to display a popup.
 */
function popupad_action_display_popup($popupad, $context = array()) {
  $popup_settings = popupad_prepare_popup($popupad);
  popupad_add_popup($popup_settings);
  popupad_save_time_cookie($popupad);
}

/**
 * Popup ad integration access callback.
 */
function popupad_integration_access($type, $name) {
  if ($type == 'event' || $type == 'condition') {
    return entity_access('view', 'popupad');
  }
}
