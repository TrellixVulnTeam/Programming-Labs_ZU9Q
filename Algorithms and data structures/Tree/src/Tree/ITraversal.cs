using System;
using System.Collections.Generic;

namespace Tree
{
    public interface IBFSTraversalable<TKey, TValue>
                    where TKey : IComparable<TKey>
    {
        IEnumerable<BSTNode<TKey, TValue>> BFS();
    }

    public interface IPostOrderTraversalable<TKey, TValue>
                    where TKey : IComparable<TKey>
    {
        IEnumerable<BSTNode<TKey, TValue>> PostOrderTraversal();
    }

    public interface IInOrderTraversalable<TKey, TValue>
                    where TKey : IComparable<TKey>
    {
        IEnumerable<BSTNode<TKey, TValue>> InOrderTraversal();
    }

    public interface IDFSTraversalable<TKey, TValue>
                    where TKey : IComparable<TKey>
    {
        IEnumerable<BSTNode<TKey, TValue>> DFS();
    }
}