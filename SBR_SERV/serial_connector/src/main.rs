
mod node;
use node::Node;


fn main() {
    let mut node_linux: Node = Node::new(String::from("/dev/ttyS0"), 460800, 3000);

    loop{
        node_linux.run();
    }
    

}
