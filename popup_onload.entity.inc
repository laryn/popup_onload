<?php

/**
 * @file
 * Popupad entity model and controller classes.
 */

/**
 * The class used for popup_onload entities.
 */
class PopupOnLoad
extends Entity {

  /**
   * Entity constructor.
   */
  public function __construct($values = array()) {
    parent::__construct($values, 'popup_onload');
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
 * PopupOnLoadControllerController extends DrupalDefaultEntityController.
 */
class PopupOnLoadController
extends EntityAPIController {

  /**
   * Controller constructor.
   */
  public function __construct($entityType) {
    parent::__construct($entityType);
  }

  /**
   * Create a popup_onload.
   * @see EntityAPIController::create()
   */
  public function create(array $values = array()) {
    // Add values that are specific to our popup_onload.
    $values += array(
      'popup_id' => '',
      'bundle_type' => 'popup_onload_basic',
      'is_new' => TRUE,
      'language' => '',
      'name' => '',
      'body' => '',
      'format' => '',
      'width' => 0,
      'height' => 0,
      'fixed_position' => 0,
    );

    $popup_onload = parent::create($values);
    return $popup_onload;
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
