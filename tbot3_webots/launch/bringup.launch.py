import os
import launch
import launch_ros

from ament_index_python.packages import get_package_share_directory
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.event_handlers import OnProcessStart

def generate_launch_description():
    pkg_webots = get_package_share_directory("tbot3_webots")
    pkg_teleop = get_package_share_directory("tbot3_teleop")
    pkg_costmap = get_package_share_directory("tbot3_costmap")

    simulation = launch.actions.IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_webots, "launch", "tbot3_webots_proto.launch.py")
        )
    )

    teleop = launch .actions.IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_teleop, "launch", "joy_teleop.launch.py")
        )
    )

    costmap = launch.actions.IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_costmap, 'launch', "costmap_2d.launch.py")
        )
    )

    scan_norm = launch_ros.actions.Node(
        package='data_preprocessing',
        executable='scan_normalizer',
        output='screen',
        parameters=[{'use_unit_range': False}]
    )

    return launch.launch_description.LaunchDescription([
        simulation,
        # teleop,
        launch.actions.TimerAction(
            period=6.0,
            actions=[costmap]
        ),
        launch.actions.TimerAction(
            period=1.0,
            actions=[scan_norm]
        )
    ])