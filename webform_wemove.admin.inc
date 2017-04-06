<?php

function webform_wemove_admin_settings_form($form, &$form_state) {

  /************************/
  /***** YouMove Part *****/
  /************************/
  
  $form['ymw_ID'] = array(
    '#type' => 'textfield',
    '#title' => t('Webform ID'),
    '#default_value' => variable_get('webform_wemove__ymw_ID',null),
    '#size' => 4,
    '#maxlength' => 4,
    '#required' => TRUE,
  );
  $form['ymw_indicator_ID'] = array(
    '#type' => 'textfield',
    '#title' => t('Webform contact types field key'),
    '#default_value' => variable_get('webform_wemove__ymw_indicator_ID',null),
    '#required' => TRUE,
  );

  $contact_types = variable_get('webform_wemove__ymw_contact_types',null);
  $form_components = variable_get('webform_wemove__ymw_components',null);
  
  foreach($contact_types as $contact_type) {
    $form['ymw_'.$contact_type] = array(
      '#type' => 'fieldset',
      '#title' => t('Contact: '.$contact_type),
      '#collapsible' => false,
    );
       
    foreach($form_components as $form_component) {
      $form['ymw_'.$contact_type]['ymw_'.$contact_type.'_'.$form_component['name']] = array(
        '#type' => 'textfield',
        '#title' => $form_component['label'],
        '#default_value' => variable_get(webform_wemove__ymw_settings)[$contact_type][$form_component['name']],
        '#required' => TRUE,
      );
    }
  }
  
  $form['ymw_disabled_fields'] = array(
    '#type' => 'textarea',
    '#title' => t('Webform disabled fields (edition)'),
    '#default_value' => variable_get('webform_wemove__ymw_settings')['disabled_fields'],
    '#required' => TRUE,
    '#description' => t('Field keys, separated by commas'),
  );
  
  $form['#submit'][] = '_ymw_admin_settings_submit';

  return system_settings_form($form);
}

function _ymw_admin_settings_submit($form, $form_state) {
  $contact_types = variable_get('webform_wemove__ymw_contact_types',null);
  $form_components = variable_get('webform_wemove__ymw_components',null);
  $settings = array();

  foreach($contact_types as $contact_type) {
    foreach($form_components as $form_component) {
      $settings[$contact_type][$form_component['name']] = $form_state['values']['ymw_'.$contact_type.'_'.$form_component['name']];
    }
  }
  $settings['disabled_fields'] =  $form_state['values']['ymw_disabled_fields'];

  variable_set('webform_wemove__ymw_ID', $form_state['values']['ymw_ID']);
  variable_set('webform_wemove__ymw_indicator_ID',$form_state['values']['ymw_indicator_ID']);
  variable_set('webform_wemove__ymw_settings',$settings);
}