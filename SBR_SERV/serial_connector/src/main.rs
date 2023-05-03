
mod node;
use node::Node;
use std::time::Duration;
use std::thread;


fn main() {
    let mut node_linux: Node = Node::new(String::from("/dev/ttyUSB0"), 460800);

    loop{
        node_linux.run();
        //thread::sleep(Duration::from_millis(1000));
    }
    

}
