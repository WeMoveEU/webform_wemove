<?php

function webform_wemove_admin_settings_form($form, &$form_state) {

  $form['webform_ID'] = array(
    '#type' => 'textfield',
    '#title' => t('Campaign\'s webform ID'),
    '#default_value' => variable_get('webform_wemove_webform_ID',null),
    '#size' => 4,
    '#maxlength' => 4,
    '#required' => TRUE,
  );
  $form['webform_indicator_ID'] = array(
    '#type' => 'textfield',
    '#title' => t('Webform content types field key'),
    '#default_value' => variable_get('webform_wemove_webform_indicator_ID',null),
    '#required' => TRUE,
  );

  $contact_types = variable_get('webform_wemove_schema__contact_types',null);
  $form_components = variable_get('webform_wemove_schema__components',null);
 
  foreach($contact_types as $contact_type) {
    $form[$contact_type] = array(
      '#type' => 'fieldset',
      '#title' => t('Campaign\'s webform '.$contact_type.' data'),
      '#collapsible' => false,
    );
    
    foreach($form_components as $webform_component) {
      $form[$contact_type][$contact_type.'_'.$webform_component['name']] = array(
        '#type' => 'textfield',
        '#title' => $webform_component['label'],
        '#default_value' => variable_get(webform_wemove_webform)[$contact_type][$webform_component['name']],
        '#required' => TRUE,
      );
    }
  }
  
  $form['#submit'][] = 'webform_wemove_admin_settings_submit';

  return system_settings_form($form);
}

function webform_wemove_admin_settings_submit($form, $form_state) {
  $contact_types = variable_get('webform_wemove_schema__contact_types',null);
  $form_components = variable_get('webform_wemove_schema__components',null);
  $webform_wemove_webform = array();

  foreach($contact_types as $contact_type) {
    foreach($form_components as $form_component) {
      $webform_wemove_webform[$contact_type][$form_component['name']] = $form_state['values'][$contact_type.'_'.$form_component['name']];
    }
  }

  variable_set('webform_wemove_webform_ID',$form_state['values']['webform_ID']);
  variable_set('webform_wemove_webform_indicator_ID',$form_state['values']['webform_indicator_ID']);
  variable_set('webform_wemove_webform',$webform_wemove_webform);
}