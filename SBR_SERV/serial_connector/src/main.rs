
mod node;
use node::Node;
use std::thread;

fn main() {
    let mut node_linux: Node = Node::new(String::from("/dev/ttyS0"), 460800, 3000);

    let thread_node = thread::spawn(move || {
        loop{
            node_linux.run();
        }
    });

    thread_node.join().unwrap();
    
}
