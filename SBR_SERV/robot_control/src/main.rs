
use std::{thread, time};
use std::sync::mpsc::channel;

mod graphql;
mod robot_control;
mod collect_events;

use robot_control::RobotControl;
use collect_events::CollectEvents;

fn main() {

    let (sender_control_robot, receiver_collect_events) = channel();

    let mut robot_control = RobotControl::new(receiver_collect_events);
    let mut collect_events = CollectEvents::new(sender_control_robot);

    let thread_robot_control = thread::spawn(move || {
        loop {
            robot_control.run().expect("Error in Run Robot Control");
        }
    });

    let thread_collect_events = thread::spawn(move || {
        loop {
            collect_events.run().expect("Error collecting events");
            thread::sleep(time::Duration::from_millis(50));
        }
    });

    thread_robot_control.join().expect("Error in thread robot control");
    thread_collect_events.join().expect("Error in thread collect events");

}
