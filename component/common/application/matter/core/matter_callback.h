#pragma once
#include <platform_stdlib.h>
#include <app/InteractionModelEngine.h>
#include <app-common/zap-generated/callback.h>

using namespace chip::app::Clusters;
using chip::app::ConcreteCommandPath;
using chip::app::CommandHandler;
using chip::app::DataModel::Decode;
using chip::TLV::TLVReader;

int8_t ameba_matter_command_callback_key_set_write(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_key_set_read(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_key_set_remove(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_key_set_read_all_indices(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_arm_fail_safe(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_set_regulatory_config(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_commissioning_complete(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_scan_networks(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_add_or_update_wifi_network(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_add_or_update_thread_network(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_remove_network(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_connect_network(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_reorder_network(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_open_commissioning_window(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_open_basic_commissioning_window(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_revoke_commissioning(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_attestation_request(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_certificate_chain_request(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_csr_request(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_add_noc(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_update_noc(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_update_fabric_label(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_remove_fabric(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_add_trusted_root_certificate(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_query_image(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_apply_update_request(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_notify_update_applied(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_announce_ota_provider(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_identify(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_trigger_effect(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_add_group(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_view_group(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_get_group_membership(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_remove_group(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_remove_all_groups(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_add_group_if_identifying(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_add_scene(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_view_scene(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_remove_scene(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_remove_all_scenes(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_store_scene(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_recall_scene(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_get_scene_membership(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_off(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_on(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_toggle(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_off_with_effect(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_on_with_recall_global_scene(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_on_with_timed_off(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_move_to_level(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_move(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_step(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_stop(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_move_to_level_with_on_off(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_move_with_on_off(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_step_with_on_off(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_stop_with_on_off(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_move_to_closest_frequency(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_move_to_hue(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_move_hue(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_step_hue(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_move_to_saturation(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_move_saturation(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_step_saturation(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_move_to_hue_and_saturation(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_stop_move_step(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_move_to_color_temperature(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_move_color_temperature(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_step_color_temperature(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_enhanced_move_to_hue(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_enhanced_move_hue(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_enhanced_step_hue(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_enhanced_move_to_hue_and_saturation(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_color_loop_set(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_move_to_color(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_move_color(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_step_color(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_lock_door(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_unlock_door(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_setpoint_raise_lower(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_set_weekly_schedule(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_get_weekly_schedule(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_clear_weekly_schedule(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_thread_reset_counts(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_wifi_reset_counts(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_test_event_trigger(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_up_or_open(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_down_or_close(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_stop_motion(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_go_to_lift_value(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_go_to_lift_percentage(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_go_to_tilt_value(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_go_to_tilt_percentage(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_instance_action(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_instance_action_with_transition(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_start_action(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_start_action_with_duration(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_stop_action(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_pause_action(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_pause_action_with_duration(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_resume_action(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_enable_action(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_enable_action_with_duration(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_disable_action(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);
int8_t ameba_matter_command_callback_disable_action_with_duration(const ConcreteCommandPath &command_path, TLVReader &tlv_data, void *opaque_ptr);