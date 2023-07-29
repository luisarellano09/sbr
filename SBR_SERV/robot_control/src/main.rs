mod graphql;
mod robot_control;

use robot_control::RobotControl;

fn main() {

    let mut robot_control = RobotControl::new();

    loop {
        robot_control.run().expect("Error in Run Robot Control");
    }
}
