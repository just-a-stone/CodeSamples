package com.example.tree;

import java.util.LinkedList;
import java.util.Queue;

public class BreadthFirstTraversal extends TreeTraversal {

    @SuppressWarnings("rawtypes")
    private Queue<TreeNode> nodeQueue = new LinkedList<>();

    @Override
    public <T> void traverse(TreeNode<T> node, TreeNodeVisitor visitor) {

        nodeQueue.add(node);

        // get next node from the queue, visit it and add its children to the queue
        while(nodeQueue.size() > 0) {
            @SuppressWarnings("unchecked")
            TreeNode<T> n = nodeQueue.poll();

            visitor.visit(n);
            
            for (TreeNode<T> childNode : n.getChildren()) {
                nodeQueue.add(childNode);
            }
        }
    }

}