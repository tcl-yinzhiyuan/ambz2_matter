#include "matter_node.h"
#include "matter_endpoint.h"
#include "matter_callback.h"
#include "matter_cluster.h"
#include "matter_command.h"
#include "matter_flags.h"
#include <app/PluginApplicationCallbacks.h>
#include <app-common/zap-generated/ids/Commands.h>

using namespace chip::app::Clusters;

extern Node *node;

void plugin_init_callback_common()
{
    printf("Cluster plugin init common callback\n");
    if (!node) {
        /* Skip plugin_init_callback_common when ameba matter data model is not used */
        return;
    }
    Endpoint *endpoint = node->endpoint_list;
    while (endpoint)
    {
        Cluster *cluster = endpoint->cluster_list;
        while (cluster)
        {
            /* Plugin server init callback */
            plugin_server_init_callback_t plugin_server_init_callback = cluster->get_plugin_server_init_callback();
            if (plugin_server_init_callback)
            {
                plugin_server_init_callback();
            }

            /* Plugin client init callback */
            plugin_client_init_callback_t plugin_client_init_callback = cluster->get_plugin_client_init_callback();
            if (plugin_client_init_callback) {
                plugin_client_init_callback();
            }

            /* next cluster */
            cluster = cluster->get_next();
        }
        /* next endpoint */
        endpoint = endpoint->get_next();
    }
}

Cluster::Cluster(config_t config, uint32_t _cluster_id, uint16_t _endpoint_id, uint16_t cluster_flags)
{
    flags = cluster_flags;
    endpoint_id = _endpoint_id;
    cluster_id = _cluster_id;

    // TODO: don't hardcode array size
    function_t _function_list[2] = { 0 };
    uint16_t function_flags;

    // TODO: create binding cluster for clients
    if (_cluster_id == Identify::Id)
    {
        if (flags & CLUSTER_FLAG_SERVER)
        {
            set_plugin_server_init_callback(MatterIdentifyPluginServerInitCallback);
            _function_list[0] = (function_t)emberAfIdentifyClusterServerInitCallback;
            _function_list[1] = (function_t)MatterIdentifyClusterServerAttributeChangedCallback;
            function_flags = CLUSTER_FLAG_INIT_FUNCTION | CLUSTER_FLAG_ATTRIBUTE_CHANGED_FUNCTION;
            add_function_list(_function_list, function_flags);
        }
        if (flags & CLUSTER_FLAG_CLIENT)
        {
            set_plugin_client_init_callback(MatterIdentifyPluginClientInitCallback);
        }

        cluster_id = Identify::Id;
        identify_t identify_config = config.identify;

        Attribute *cluster_revision = new Attribute(ameba_matter_uint16(identify_config.cluster_revision), Globals::Attributes::ClusterRevision::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_NONE);
        add_attribute(cluster_revision);
        Attribute *identify_time = new Attribute(ameba_matter_uint16(identify_config.identify_time), Identify::Attributes::IdentifyTime::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_WRITABLE);
        identify_time->set_bounds(ameba_matter_uint16(0x0), ameba_matter_uint16(0xFE));
        add_attribute(identify_time);
        Attribute *identify_type = new Attribute(ameba_matter_uint8(identify_config.identify_type), Identify::Attributes::IdentifyType::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_NONE);
        add_attribute(identify_type);

        Command *identify = new Command(Identify::Commands::Identify::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_identify);
        add_command(identify);
    }

    else if (_cluster_id == Groups::Id)
    {
        if (flags & CLUSTER_FLAG_SERVER)
        {
            set_plugin_server_init_callback(MatterGroupsPluginServerInitCallback);
            _function_list[0] = (function_t)emberAfGroupsClusterServerInitCallback;
            function_flags = CLUSTER_FLAG_INIT_FUNCTION;
            add_function_list(_function_list, function_flags);
        }
        if (flags & CLUSTER_FLAG_CLIENT)
        {
            set_plugin_client_init_callback(MatterGroupsPluginClientInitCallback);
        }
        
        cluster_id = Groups::Id;
        groups_t groups_config = config.groups;

        Attribute *cluster_revision = new Attribute(ameba_matter_uint16(groups_config.cluster_revision), Globals::Attributes::ClusterRevision::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_NONE);
        add_attribute(cluster_revision);
        Attribute *group_name_support = new Attribute(ameba_matter_uint16(groups_config.group_name_support), Groups::Attributes::NameSupport::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_NONE);
        add_attribute(group_name_support);

        Command *add_group = new Command(Groups::Commands::AddGroup::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_add_group);
        add_command(add_group);
        Command *view_group = new Command(Groups::Commands::ViewGroup::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_view_group);
        add_command(view_group);
        Command *get_group_membership = new Command(Groups::Commands::GetGroupMembership::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_get_group_membership);
        add_command(get_group_membership);
        Command *remove_group = new Command(Groups::Commands::RemoveGroup::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_remove_group);
        add_command(remove_group);
        Command *remove_all_groups = new Command(Groups::Commands::RemoveAllGroups::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_remove_all_groups);
        add_command(remove_all_groups);
        Command *add_group_if_identifying = new Command(Groups::Commands::AddGroupIfIdentifying::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_add_group_if_identifying);
        add_command(add_group_if_identifying);
        Command *add_group_response = new Command(Groups::Commands::AddGroupResponse::Id, cluster_id, endpoint_id, COMMAND_FLAG_GENERATED, NULL);
        add_command(add_group_response);
        Command *view_group_response = new Command(Groups::Commands::ViewGroupResponse::Id, cluster_id, endpoint_id, COMMAND_FLAG_GENERATED, NULL);
        add_command(view_group_response);
        Command *get_group_membership_response = new Command(Groups::Commands::GetGroupMembershipResponse::Id, cluster_id, endpoint_id, COMMAND_FLAG_GENERATED, NULL);
        add_command(get_group_membership_response);
        Command *remove_group_response = new Command(Groups::Commands::RemoveGroupResponse::Id, cluster_id, endpoint_id, COMMAND_FLAG_GENERATED, NULL);
        add_command(remove_group_response);
    }

    else if (_cluster_id == Scenes::Id)
    {
        if (flags & CLUSTER_FLAG_SERVER)
        {
            set_plugin_server_init_callback(MatterScenesPluginServerInitCallback);
            _function_list[0] = (function_t)emberAfScenesClusterServerInitCallback;
            function_flags = CLUSTER_FLAG_INIT_FUNCTION;
            add_function_list(_function_list, function_flags);
        }
        if (flags & CLUSTER_FLAG_CLIENT)
        {
            set_plugin_client_init_callback(MatterScenesPluginClientInitCallback);
        }
        
        cluster_id = Scenes::Id;
        scenes_t scenes_config = config.scenes;

        Attribute *cluster_revision = new Attribute(ameba_matter_uint16(scenes_config.cluster_revision), Globals::Attributes::ClusterRevision::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_NONE);
        add_attribute(cluster_revision);
        Attribute *scene_count = new Attribute(ameba_matter_uint8(scenes_config.scene_count), Scenes::Attributes::SceneCount::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_NONE);
        add_attribute(scene_count);
        Attribute *current_scene = new Attribute(ameba_matter_uint8(scenes_config.current_scene), Scenes::Attributes::CurrentScene::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_NONE);
        add_attribute(current_scene);
        Attribute *current_group = new Attribute(ameba_matter_uint16(scenes_config.current_group), Scenes::Attributes::CurrentGroup::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_NONE);
        add_attribute(current_group);
        Attribute *scene_valid = new Attribute(ameba_matter_bool(scenes_config.scene_valid), Scenes::Attributes::SceneValid::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_NONE);
        add_attribute(scene_valid);
        Attribute *scene_name_support = new Attribute(ameba_matter_uint8(scenes_config.scene_name_support), Scenes::Attributes::NameSupport::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_NONE);
        add_attribute(scene_name_support);

        Command *add_scene = new Command(Scenes::Commands::AddScene::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_add_scene);
        add_command(add_scene);
        Command *view_scene = new Command(Scenes::Commands::ViewScene::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_view_scene);
        add_command(view_scene);
        Command *remove_scene = new Command(Scenes::Commands::RemoveScene::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_remove_scene);
        add_command(remove_scene);
        Command *remove_all_scenes = new Command(Scenes::Commands::RemoveAllScenes::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_remove_all_scenes);
        add_command(remove_all_scenes);
        Command *store_scene = new Command(Scenes::Commands::StoreScene::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_store_scene);
        add_command(store_scene);
        Command *recall_scene = new Command(Scenes::Commands::RecallScene::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_recall_scene);
        add_command(recall_scene);
        Command *get_scene_membership = new Command(Scenes::Commands::GetSceneMembership::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_get_scene_membership);
        add_command(get_scene_membership);
        Command *add_scene_response = new Command(Scenes::Commands::AddSceneResponse::Id, cluster_id, endpoint_id, COMMAND_FLAG_GENERATED, NULL);
        add_command(add_scene_response);
        Command *view_scene_response = new Command(Scenes::Commands::ViewSceneResponse::Id, cluster_id, endpoint_id, COMMAND_FLAG_GENERATED, NULL);
        add_command(view_scene_response);
        Command *remove_scene_response = new Command(Scenes::Commands::RemoveSceneResponse::Id, cluster_id, endpoint_id, COMMAND_FLAG_GENERATED, NULL);
        add_command(remove_scene_response);
        Command *remove_all_scenes_response = new Command(Scenes::Commands::RemoveAllScenesResponse::Id, cluster_id, endpoint_id, COMMAND_FLAG_GENERATED, NULL);
        add_command(remove_all_scenes_response);
        Command *store_scene_response = new Command(Scenes::Commands::StoreSceneResponse::Id, cluster_id, endpoint_id, COMMAND_FLAG_GENERATED, NULL);
        add_command(store_scene_response);
        Command *get_scene_membership_response = new Command(Scenes::Commands::GetSceneMembershipResponse::Id, cluster_id, endpoint_id, COMMAND_FLAG_GENERATED, NULL);
        add_command(get_scene_membership_response);
    }

    else if (_cluster_id == OnOff::Id)
    {
        if (flags & CLUSTER_FLAG_SERVER)
        {
            set_plugin_server_init_callback(MatterOnOffPluginServerInitCallback);
            _function_list[0] = (function_t)emberAfOnOffClusterServerInitCallback;
            function_flags = CLUSTER_FLAG_INIT_FUNCTION;
            add_function_list(_function_list, function_flags);
        }
        if (flags & CLUSTER_FLAG_CLIENT)
        {
            set_plugin_client_init_callback(MatterOnOffPluginClientInitCallback);
        }
        
        cluster_id = OnOff::Id;
        on_off_t on_off_config = config.on_off;

        Attribute *cluster_revision = new Attribute(ameba_matter_uint16(on_off_config.cluster_revision), Globals::Attributes::ClusterRevision::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_NONE);
        add_attribute(cluster_revision);
        Attribute *onoff = new Attribute(ameba_matter_bool(on_off_config.onoff), OnOff::Attributes::OnOff::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_NONVOLATILE);
        add_attribute(onoff);

        Command *off = new Command(OnOff::Commands::Off::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_off);
        add_command(off);
        Command *on = new Command(OnOff::Commands::On::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_on);
        add_command(on);
        Command *toggle = new Command(OnOff::Commands::Toggle::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_toggle);
        add_command(toggle);

        if (on_off_config.featuremap & (uint32_t) OnOff::OnOffFeature::kLighting) 
        {
            //add extra attributes and commands
            Attribute *global_scene_control = new Attribute(ameba_matter_bool(on_off_config.global_scene_control), OnOff::Attributes::GlobalSceneControl::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_NONE);
            add_attribute(global_scene_control);
            Attribute *on_time = new Attribute(ameba_matter_nullable_uint16(on_off_config.on_time), OnOff::Attributes::OnTime::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_WRITABLE | ATTRIBUTE_FLAG_NULLABLE);
            add_attribute(on_time);
            Attribute *off_wait_time = new Attribute(ameba_matter_nullable_uint16(on_off_config.off_wait_time), OnOff::Attributes::OffWaitTime::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_WRITABLE | ATTRIBUTE_FLAG_NULLABLE);
            add_attribute(off_wait_time);
            Attribute *start_up_on_off = new Attribute(ameba_matter_nullable_uint8(on_off_config.start_up_on_off), OnOff::Attributes::StartUpOnOff::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_WRITABLE | ATTRIBUTE_FLAG_NONVOLATILE | ATTRIBUTE_FLAG_NULLABLE);
            add_attribute(start_up_on_off);

            Command *off_with_effect = new Command(OnOff::Commands::OffWithEffect::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_off_with_effect);
            add_command(off_with_effect);
            Command *on_with_recall_global_scene = new Command(OnOff::Commands::OnWithRecallGlobalScene::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_on_with_recall_global_scene);
            add_command(on_with_recall_global_scene);
            Command *on_with_timed_off = new Command(OnOff::Commands::OnWithTimedOff::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_on_with_timed_off);
            add_command(on_with_timed_off);
        }
    }

    else if (_cluster_id == LevelControl::Id)
    {
        if (flags & CLUSTER_FLAG_SERVER)
        {
            set_plugin_server_init_callback(MatterLevelControlPluginServerInitCallback);
            _function_list[0] = (function_t)emberAfLevelControlClusterServerInitCallback;
            function_flags = CLUSTER_FLAG_INIT_FUNCTION;
            add_function_list(_function_list, function_flags);
        }
        if (flags & CLUSTER_FLAG_CLIENT)
        {
            set_plugin_client_init_callback(MatterLevelControlPluginClientInitCallback);
        }
        
        cluster_id = LevelControl::Id;
        level_control_t level_control_config = config.level_control;

        Attribute *cluster_revision = new Attribute(ameba_matter_uint16(level_control_config.cluster_revision), Globals::Attributes::ClusterRevision::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_NONE);
        add_attribute(cluster_revision);
        Attribute *current_level = new Attribute(ameba_matter_nullable_uint8(level_control_config.current_level), LevelControl::Attributes::CurrentLevel::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_NONVOLATILE | ATTRIBUTE_FLAG_NULLABLE);
        add_attribute(current_level);
        Attribute *on_level = new Attribute(ameba_matter_nullable_uint8(level_control_config.on_level), LevelControl::Attributes::OnLevel::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_WRITABLE | ATTRIBUTE_FLAG_NULLABLE);
        add_attribute(on_level);
        Attribute *options = new Attribute(ameba_matter_uint8(level_control_config.options), LevelControl::Attributes::Options::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_WRITABLE);
        options->set_bounds(ameba_matter_bitmap8(0x0), ameba_matter_bitmap8(0x3));
        add_attribute(options);

        Command *move_to_level = new Command(LevelControl::Commands::MoveToLevel::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_move_to_level);
        add_command(move_to_level);
        Command *move = new Command(LevelControl::Commands::Move::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_move);
        add_command(move);
        Command *step = new Command(LevelControl::Commands::Step::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_step);
        add_command(step);
        Command *stop = new Command(LevelControl::Commands::Stop::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_stop);
        add_command(stop);
        Command *move_to_level_with_on_off = new Command(LevelControl::Commands::MoveToLevelWithOnOff::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_move_to_level_with_on_off);
        add_command(move_to_level_with_on_off);
        Command *move_with_on_off = new Command(LevelControl::Commands::MoveWithOnOff::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_move_with_on_off);
        add_command(move_with_on_off);
        Command *step_with_on_off = new Command(LevelControl::Commands::StepWithOnOff::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_step_with_on_off);
        add_command(step_with_on_off);
        Command *stop_with_on_off = new Command(LevelControl::Commands::StopWithOnOff::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_stop_with_on_off);
        add_command(stop_with_on_off);

        if (level_control_config.featuremap & (uint32_t) LevelControl::LevelControlFeature::kOnOff) 
        {
            // no attributes & commands at the moment
        }
        if (level_control_config.featuremap & (uint32_t) LevelControl::LevelControlFeature::kLighting) 
        {
            Attribute *remaining_time = new Attribute(ameba_matter_uint16(level_control_config.remaining_time), LevelControl::Attributes::RemainingTime::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_NONE);
            add_attribute(remaining_time);
            Attribute *min_level = new Attribute(ameba_matter_uint8(level_control_config.min_level), LevelControl::Attributes::MinLevel::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_NONE);
            add_attribute(min_level);
            Attribute *max_level = new Attribute(ameba_matter_uint8(level_control_config.max_level), LevelControl::Attributes::MaxLevel::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_NONE);
            add_attribute(max_level);
            Attribute *start_up_current_level = new Attribute(ameba_matter_nullable_uint8(level_control_config.start_up_current_level), LevelControl::Attributes::StartUpCurrentLevel::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_WRITABLE | ATTRIBUTE_FLAG_NULLABLE | ATTRIBUTE_FLAG_NONVOLATILE);
            add_attribute(max_level);
        }
    }

    else if (_cluster_id == BasicInformation::Id)
    {
        if (flags & CLUSTER_FLAG_SERVER)
        {
            set_plugin_server_init_callback(MatterBasicInformationPluginServerInitCallback);
            _function_list[0] = (function_t)emberAfBasicInformationClusterServerInitCallback;
            function_flags = CLUSTER_FLAG_INIT_FUNCTION;
            add_function_list(_function_list, function_flags);
        }
        if (flags & CLUSTER_FLAG_CLIENT)
        {
            set_plugin_client_init_callback(MatterBasicInformationPluginClientInitCallback);
        }
        
        cluster_id = BasicInformation::Id;
        basic_information_t basic_information_config = config.basic_information;

        Attribute *cluster_revision = new Attribute(ameba_matter_uint16(basic_information_config.cluster_revision), Globals::Attributes::ClusterRevision::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_NONE);
        add_attribute(cluster_revision);
        Attribute *node_label = new Attribute(ameba_matter_char_str(basic_information_config.node_label, sizeof(basic_information_config.node_label)), BasicInformation::Attributes::NodeLabel::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_WRITABLE | ATTRIBUTE_FLAG_NONVOLATILE);
        add_attribute(node_label);
    }

    else if (_cluster_id == GeneralCommissioning::Id)
    {
        if (flags & CLUSTER_FLAG_SERVER)
        {
            set_plugin_server_init_callback(MatterGeneralCommissioningPluginServerInitCallback);
            function_flags = CLUSTER_FLAG_NONE;
            add_function_list(_function_list, function_flags);
        }
        if (flags & CLUSTER_FLAG_CLIENT)
        {
            set_plugin_client_init_callback(MatterGeneralCommissioningPluginClientInitCallback);
        }
        
        cluster_id = GeneralCommissioning::Id;
        general_commissioning_t general_commissioning_config = config.general_commissioning;

        Attribute *cluster_revision = new Attribute(ameba_matter_uint16(general_commissioning_config.cluster_revision), Globals::Attributes::ClusterRevision::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_NONE);
        add_attribute(cluster_revision);
        Attribute *breadcrumb = new Attribute(ameba_matter_uint64(general_commissioning_config.breadcrumb), GeneralCommissioning::Attributes::Breadcrumb::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_WRITABLE);
        add_attribute(breadcrumb);

        Command *arm_fail_safe = new Command(GeneralCommissioning::Commands::ArmFailSafe::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_arm_fail_safe);
        add_command(arm_fail_safe);
        Command *arm_fail_safe_response = new Command(GeneralCommissioning::Commands::ArmFailSafeResponse::Id, cluster_id, endpoint_id, COMMAND_FLAG_GENERATED, NULL);
        add_command(arm_fail_safe_response);
        Command *set_regulatory_config = new Command(GeneralCommissioning::Commands::SetRegulatoryConfig::Id, cluster_id, endpoint_id, COMMAND_FLAG_GENERATED, NULL);
        add_command(set_regulatory_config);
        Command *set_regulatory_config_response = new Command(GeneralCommissioning::Commands::SetRegulatoryConfigResponse::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, NULL);
        add_command(set_regulatory_config_response);
        Command *commissioning_complete = new Command(GeneralCommissioning::Commands::CommissioningComplete::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, NULL);
        add_command(commissioning_complete);
        Command *commissioning_complete_response = new Command(GeneralCommissioning::Commands::CommissioningCompleteResponse::Id, cluster_id, endpoint_id, COMMAND_FLAG_GENERATED, NULL);
        add_command(commissioning_complete_response);
    }

    else if (_cluster_id == NetworkCommissioning::Id)
    {
        if (flags & CLUSTER_FLAG_SERVER)
        {
            set_plugin_server_init_callback(MatterNetworkCommissioningPluginServerInitCallback);
            function_flags = CLUSTER_FLAG_NONE;
            add_function_list(_function_list, function_flags);
        }
        if (flags & CLUSTER_FLAG_CLIENT)
        {
            set_plugin_client_init_callback(MatterNetworkCommissioningPluginClientInitCallback);
        }
        
        cluster_id = NetworkCommissioning::Id;
        network_commissioning_t network_commissioning_config = config.network_commissioning;

        Attribute *cluster_revision = new Attribute(ameba_matter_uint16(network_commissioning_config.cluster_revision), Globals::Attributes::ClusterRevision::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_NONE);
        add_attribute(cluster_revision);

        Command *scan_networks = new Command(NetworkCommissioning::Commands::ScanNetworks::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_scan_networks);
        add_command(scan_networks);
        Command *scan_networks_response = new Command(NetworkCommissioning::Commands::ScanNetworksResponse::Id, cluster_id, endpoint_id, COMMAND_FLAG_GENERATED, NULL);
        add_command(scan_networks_response);
        Command *add_or_update_wifi_network = new Command(NetworkCommissioning::Commands::AddOrUpdateWiFiNetwork::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_add_or_update_wifi_network);
        add_command(add_or_update_wifi_network);
        Command *add_or_update_thread_network = new Command(NetworkCommissioning::Commands::AddOrUpdateThreadNetwork::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_add_or_update_thread_network);
        add_command(add_or_update_thread_network);
        Command *remove_network = new Command(NetworkCommissioning::Commands::RemoveNetwork::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_remove_network);
        add_command(remove_network);
        Command *network_config_response = new Command(NetworkCommissioning::Commands::NetworkConfigResponse::Id, cluster_id, endpoint_id, COMMAND_FLAG_GENERATED, NULL);
        add_command(network_config_response);
        Command *connect_network = new Command(NetworkCommissioning::Commands::ConnectNetwork::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_connect_network);
        add_command(connect_network);
        Command *connect_network_response = new Command(NetworkCommissioning::Commands::ConnectNetworkResponse::Id, cluster_id, endpoint_id, COMMAND_FLAG_GENERATED, NULL);
        add_command(connect_network_response);
        Command *reorder_network = new Command(NetworkCommissioning::Commands::ReorderNetwork::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_reorder_network);
        add_command(reorder_network);
    }

    else if (_cluster_id == GeneralDiagnostics::Id)
    {
        if (flags & CLUSTER_FLAG_SERVER)
        {
            set_plugin_server_init_callback(MatterGeneralDiagnosticsPluginServerInitCallback);
            function_flags = CLUSTER_FLAG_NONE;
            add_function_list(_function_list, function_flags);
        }
        if (flags & CLUSTER_FLAG_CLIENT)
        {
            set_plugin_client_init_callback(MatterGeneralDiagnosticsPluginClientInitCallback);
        }
        
        cluster_id = GeneralDiagnostics::Id;
        general_diagnostics_t general_diagnostics_config = config.general_diagnostics;

        Attribute *cluster_revision = new Attribute(ameba_matter_uint16(general_diagnostics_config.cluster_revision), Globals::Attributes::ClusterRevision::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_NONE);
        add_attribute(cluster_revision);

        Command *test_event_trigger = new Command(GeneralDiagnostics::Commands::TestEventTrigger::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_test_event_trigger);
        add_command(test_event_trigger);
    }

#if 0 // thread enabled
    else if (_cluster_id == ThreadNetworkDiagnostics::Id)
    {
        if (flags & CLUSTER_FLAG_SERVER)
        {
            set_plugin_server_init_callback(MatterThreadNetworkDiagnosticsPluginServerInitCallback);
            function_flags = CLUSTER_FLAG_NONE;
            add_function_list(_function_list, function_flags);
        }
        if (flags & CLUSTER_FLAG_CLIENT)
        {
            set_plugin_client_init_callback(MatterThreadNetworkDiagnosticsPluginClientInitCallback);
        }
        
        cluster_id = ThreadNetworkDiagnostics::Id;
        diagnostics_network_thread_t diagnostics_network_thread_config = config.diagnostics_network_thread;

        Attribute *cluster_revision = new Attribute(ameba_matter_uint16(diagnostics_network_thread_config.cluster_revision), Globals::Attributes::ClusterRevision::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_NONE);
        add_attribute(cluster_revision);
    }
#endif

#if 1 // wifi enabled
    else if (_cluster_id == WiFiNetworkDiagnostics::Id)
    {
        if (flags & CLUSTER_FLAG_SERVER)
        {
            set_plugin_server_init_callback(MatterWiFiNetworkDiagnosticsPluginServerInitCallback);
            function_flags = CLUSTER_FLAG_NONE;
            add_function_list(_function_list, function_flags);
        }
        if (flags & CLUSTER_FLAG_CLIENT)
        {
            set_plugin_client_init_callback(MatterWiFiNetworkDiagnosticsPluginClientInitCallback);
        }
        
        cluster_id = WiFiNetworkDiagnostics::Id;
        diagnostics_network_wifi_t diagnostics_network_wifi_config = config.diagnostics_network_wifi;

        Attribute *cluster_revision = new Attribute(ameba_matter_uint16(diagnostics_network_wifi_config.cluster_revision), Globals::Attributes::ClusterRevision::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_NONE);
        add_attribute(cluster_revision);
    }
#endif

    else if (_cluster_id == AdministratorCommissioning::Id)
    {
        if (flags & CLUSTER_FLAG_SERVER)
        {
            set_plugin_server_init_callback(MatterAdministratorCommissioningPluginServerInitCallback);
            function_flags = CLUSTER_FLAG_NONE;
            add_function_list(_function_list, function_flags);
        }
        if (flags & CLUSTER_FLAG_CLIENT)
        {
            set_plugin_client_init_callback(MatterAdministratorCommissioningPluginClientInitCallback);
        }
        
        cluster_id = AdministratorCommissioning::Id;
        administrator_commissioning_t administrator_commissioning_config = config.administrator_commissioning;

        Attribute *cluster_revision = new Attribute(ameba_matter_uint16(administrator_commissioning_config.cluster_revision), Globals::Attributes::ClusterRevision::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_NONE);
        add_attribute(cluster_revision);

        Command *open_commissioning_window = new Command(AdministratorCommissioning::Commands::OpenCommissioningWindow::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_open_commissioning_window);
        add_command(open_commissioning_window);
        Command *open_basic_commissioning_window = new Command(AdministratorCommissioning::Commands::OpenBasicCommissioningWindow::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_open_basic_commissioning_window);
        add_command(open_basic_commissioning_window);
        Command *revoke_commissioning = new Command(AdministratorCommissioning::Commands::RevokeCommissioning::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_revoke_commissioning);
        add_command(revoke_commissioning);
    }

    else if (_cluster_id == OperationalCredentials::Id)
    {
        if (flags & CLUSTER_FLAG_SERVER)
        {
            set_plugin_server_init_callback(MatterOperationalCredentialsPluginServerInitCallback);
            function_flags = CLUSTER_FLAG_NONE;
            add_function_list(_function_list, function_flags);
        }
        if (flags & CLUSTER_FLAG_CLIENT)
        {
            set_plugin_client_init_callback(MatterOperationalCredentialsPluginClientInitCallback);
        }
        
        cluster_id = OperationalCredentials::Id;
        operational_credentials_t operational_credentials_config = config.operational_credentials;

        Attribute *cluster_revision = new Attribute(ameba_matter_uint16(operational_credentials_config.cluster_revision), Globals::Attributes::ClusterRevision::Id, cluster_id, endpoint_id, ATTRIBUTE_FLAG_NONE);
        add_attribute(cluster_revision);

        Command *attestation_request = new Command(OperationalCredentials::Commands::AttestationRequest::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_attestation_request);
        add_command(attestation_request);
        Command *attestation_response = new Command(OperationalCredentials::Commands::AttestationResponse::Id, cluster_id, endpoint_id, COMMAND_FLAG_GENERATED, NULL);
        add_command(attestation_response);
        Command *certificate_chain_request = new Command(OperationalCredentials::Commands::CertificateChainRequest::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_certificate_chain_request);
        add_command(certificate_chain_request);
        Command *certificate_chain_response = new Command(OperationalCredentials::Commands::CertificateChainResponse::Id, cluster_id, endpoint_id, COMMAND_FLAG_GENERATED, NULL);
        add_command(certificate_chain_response);
        Command *csr_request = new Command(OperationalCredentials::Commands::CSRRequest::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_csr_request);
        add_command(csr_request);
        Command *csr_response = new Command(OperationalCredentials::Commands::CSRResponse::Id, cluster_id, endpoint_id, COMMAND_FLAG_GENERATED, NULL);
        add_command(csr_response);
        Command *add_noc = new Command(OperationalCredentials::Commands::AddNOC::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_add_noc);
        add_command(add_noc);
        Command *update_noc = new Command(OperationalCredentials::Commands::UpdateNOC::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_update_noc);
        add_command(update_noc);
        Command *noc_response = new Command(OperationalCredentials::Commands::NOCResponse::Id, cluster_id, endpoint_id, COMMAND_FLAG_GENERATED, NULL);
        add_command(noc_response);
        Command *update_fabric_label = new Command(OperationalCredentials::Commands::UpdateFabricLabel::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_update_fabric_label);
        add_command(update_fabric_label);
        Command *remove_fabric = new Command(OperationalCredentials::Commands::RemoveFabric::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_remove_fabric);
        add_command(remove_fabric);
        Command *add_trusted_root_certificate = new Command(OperationalCredentials::Commands::AddTrustedRootCertificate::Id, cluster_id, endpoint_id, COMMAND_FLAG_ACCEPTED, ameba_matter_command_callback_add_trusted_root_certificate);
        add_command(add_trusted_root_certificate);
    }
}

Cluster *Cluster::get_next()
{
    return next;
}

void Cluster::set_next(Cluster *cluster)
{
    next = cluster;
}

Attribute *Cluster::get_attribute_by_id(uint32_t attribute_id)
{
    Attribute *current_attribute = attribute_list;
    while (current_attribute)
    {
        if (current_attribute->attribute_id == attribute_id)
        {
            break;
        }
        current_attribute = current_attribute->get_next();
    }
    return current_attribute;
}

Command *Cluster::get_command_by_id(uint32_t command_id, uint16_t command_flags)
{
    Command *current_command = command_list;
    while (current_command)
    {
        if ((current_command->command_id == command_id) && (current_command->flags & command_flags))
        {
            break;
        }
        current_command = current_command->get_next();
    }
    return current_command;
}

void Cluster::add_attribute(Attribute *attribute)
{
    Attribute *previous_attribute = NULL;
    Attribute *current_attribute = attribute_list;
    while (current_attribute)
    {
        previous_attribute = current_attribute;
        current_attribute = current_attribute->get_next();
    }
    if (previous_attribute == NULL)
    {
        attribute_list = attribute;
    }
    else
    {
        previous_attribute->set_next(attribute);
    }
}

void Cluster::add_command(Command *command)
{
    Command *previous_command = NULL;
    Command *current_command = command_list;
    while (current_command)
    {
        previous_command = current_command;
        current_command = current_command->get_next();
    }
    if (previous_command == NULL)
    {
        command_list = command;
    }
    else
    {
        previous_command->set_next(command);
    }
}

int8_t Cluster::add_function_list(function_t *_function_list, int function_flags)
{
    function_list = _function_list;
    flags |= function_flags;
    return 0;
}

void Cluster::set_plugin_server_init_callback(plugin_server_init_callback_t callback)
{
    plugin_server_init_callback = callback;
}

void Cluster::set_plugin_client_init_callback(plugin_client_init_callback_t callback)
{
    plugin_client_init_callback = callback;
}

plugin_server_init_callback_t Cluster::get_plugin_server_init_callback(void)
{
    return plugin_server_init_callback;
}

plugin_client_init_callback_t Cluster::get_plugin_client_init_callback(void)
{
    return plugin_client_init_callback;
}
