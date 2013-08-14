<?php

/**
 * @file
 * Popupad entity model and controller classes.
 */

/**
 * The class used for popupad entities.
 */
class PopupAd
extends Entity {

  /**
   * Entity constructor.
   */
  public function __construct($values = array()) {
    parent::__construct($values, 'popupad');
  }

  /**
   * Overriden default entity label callback.
   * @see Entity::defaultLabel()
   */
  protected function defaultLabel() {
    return $this->name;
  }

}

/**
 * PopupAdControllerController extends DrupalDefaultEntityController.
 */
class PopupAdController
extends EntityAPIController {

  /**
   * Controller constructor.
   */
  public function __construct($entityType) {
    parent::__construct($entityType);
  }

  /**
   * Create a popupad.
   * @see EntityAPIController::create()
   */
  public function create(array $values = array()) {
    // Add values that are specific to our popupad.
    $values += array(
      'popup_id' => '',
      'bundle_type' => 'popupad_ad',
      'is_new' => TRUE,
      'language' => '',
      'name' => '',
      'body' => '',
      'format' => '',
      'width' => 0,
      'height' => 0,
      'fixed_position' => 0,
    );

    $popupad = parent::create($values);
    return $popupad;
  }

  /**
   * Save the popup.
   * @see EntityAPIController::save()
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    // Make use of the formatted body field.
    $entity->format = $entity->body['format'];
    $entity->body = $entity->body['value'];
    parent::save($entity, $transaction);
  }

}
