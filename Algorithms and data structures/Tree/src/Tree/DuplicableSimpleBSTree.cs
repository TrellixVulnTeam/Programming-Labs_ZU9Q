using System;
using System.Collections.Generic;

namespace Tree
{
    /// <summary>
    /// Store element in tree structure with count
    /// Provide BFS, DFS, InOrder, PostOrder traversals
    /// </summary>
    /// <typeparam name="TKey">Type of key</typeparam>
    /// <typeparam name="TValue">Type of value</typeparam>
    public class DuplicableSimpleBSTree<TKey, TValue> : BSTreeBase<TKey, TValue>,
        IInOrderTraversalable<TKey, TValue>,
        IPostOrderTraversalable<TKey, TValue>,
        IBFSTraversalable<TKey, TValue>,
        IDFSTraversalable<TKey, TValue>
        where TKey : IComparable<TKey>
    {
        private readonly IDictionary<TKey, int> counts = new Dictionary<TKey, int>();

        public DuplicableSimpleBSTree() { }

        public DuplicableSimpleBSTree(BSTNode<TKey, TValue> root)
        {
            this.Root = root;
        }

        public DuplicableSimpleBSTree(TKey rootKey, TValue rootValue)
        {
            Root = new BSTNode<TKey, TValue>(rootKey, rootValue);
        }

        /// <summary>
        /// Add element to tree
        /// If already exists, increase count(value does not update)
        /// </summary>
        public override void Add(TKey key, TValue value)
        {
            if (key == null || value == null)
                throw new System.ArgumentNullException();

            if (counts.ContainsKey(key))
            {
                counts[key]++;
            }
            else
            {
                var newNode = new BSTNode<TKey, TValue>(key, value);

                if (Root == null)
                {
                    Root = newNode;
                    counts.Add(key, 1);
                    return;
                }

                BSTNode<TKey, TValue> parent = null;
                BSTNode<TKey, TValue> current = Root;

                while (current != null)
                {
                    parent = current;
                    if (current.Key.CompareTo(key) > 0)
                        current = current.Left;
                    else
                        current = current.Right;
                }

                if (parent.Key.CompareTo(key) > 0)
                    parent.Left = newNode;
                else if (parent.Key.CompareTo(key) < 0)
                    parent.Right = newNode;

                newNode.Parent = parent;
                counts.Add(key, 1);
            }
        }

        public override void Remove(TKey key)
        {
            if (key == null)
                throw new ArgumentNullException("key is null");

            if (counts.ContainsKey(key))
            {
                RemoveFromTree(key);
                counts.Remove(key);
            }
        }

        /// <summary>
        /// Decrease count of element
        /// If argument greate than real count remove from tree
        /// </summary>
        /// <param name="key"></param>
        /// <param name="count"></param>
        public void Remove(TKey key, int count)
        {
            if (key == null)
                throw new ArgumentNullException("key is null");

            if (counts.ContainsKey(key))
            {
                if (counts[key] > count)
                    counts[key] -= count;
                else
                {
                    RemoveFromTree(key);
                    counts.Remove(key);
                }
            }
        }

        public IDictionary<TKey, int> GetKeyCounts()
        {
            return counts;
        }

        public int GetKeyCount(TKey key)
        {
            if (!counts.ContainsKey(key))
                throw new ArgumentException("Tree does not contain key");
            return counts[key];
        }


        private void RemoveFromTree(TKey key)
        {
            var current = Root;

            while (current != null)
            {
                if (current.Key.CompareTo(key) > 0)
                    current = current.Left;
                else if (current.Key.CompareTo(key) < 0)
                    current = current.Right;
                else
                {
                    if (current.Left != null && current.Right != null)
                    {
                        var min = MinFromNode(current.Right);

                        min.Left = current.Left;
                        if (current.Left != null)
                            current.Left.Parent = min;

                        if (min.Key.CompareTo(current.Right.Key) != 0)
                        {
                            min.Right = current.Right;
                            if (current.Right != null)
                                current.Right.Parent = min;
                        }

                        if (min.Parent.Left.Key.CompareTo(min.Key) == 0)
                            min.Parent.Left = null;
                        else
                            min.Parent.Right = null;

                        Swap(current, min);
                    }
                    else if (current.Right != null)
                        Swap(current, current.Right);
                    else if (current.Left != null)
                        Swap(current, current.Left);
                    else
                        Swap(current, null);
                    break;
                }
            }
        }

        private void Swap(BSTNode<TKey, TValue> source, BSTNode<TKey, TValue> destination)
        {
            if (source.Key.CompareTo(Root.Key) == 0)
                Root = destination;

            if (destination != null)
                destination.Parent = source.Parent;

            if (source.Parent != null)
            {
                if (source.Parent.Left != null)
                {
                    if (source.Parent.Left.Key.CompareTo(source.Key) == 0)
                    {
                        source.Parent.Left = destination;
                        return;
                    }
                }
                source.Parent.Right = destination;
            }
        }

        public IEnumerable<BSTNode<TKey, TValue>> InOrderTraversal()
        {
            if (Root == null)
                yield break;

            var stash = new Stack<BSTNode<TKey, TValue>>();
            TreeToStash(stash, Root);

            while (stash.Count != 0)
            {
                var current = stash.Pop();

                if (current.Right != null && stash.Count > 0 && current.Right.Key.CompareTo(stash.Peek().Key) == 0)
                {
                    TreeToStash(stash, stash.Pop());
                }

                var count = counts[current.Key];
                for (int i = 0; i < count; i++)
                    yield return current;
            }
        }

        public IEnumerable<BSTNode<TKey, TValue>> PostOrderTraversal()
        {
            if (Root == null)
                yield break;

            var stash = new Stack<BSTNode<TKey, TValue>>();
            TreeToStash(stash, Root);

            while (stash.Count != 0)
            {
                var current = stash.Pop();

                if (current.Right != null && stash.Count > 0 && current.Right.Key.CompareTo(stash.Peek().Key) == 0)
                {
                    var right = stash.Pop();
                    stash.Push(current);

                    TreeToStash(stash, right);
                    current = stash.Pop();
                }

                var count = counts[current.Key];
                for (int i = 0; i < count; i++)
                    yield return current;
            }
        }

        private void TreeToStash(Stack<BSTNode<TKey, TValue>> stash, BSTNode<TKey, TValue> temp)
        {
            while (temp != null)
            {
                if (temp.Right != null)
                    stash.Push(temp.Right);
                stash.Push(temp);
                temp = temp.Left;
            }
        }

        public IEnumerable<BSTNode<TKey, TValue>> BFS()
        {
            if (Root == null)
                yield break;

            var queue = new Queue<BSTNode<TKey, TValue>>();
            queue.Enqueue(Root);

            while (queue.Count > 0)
            {
                var current = queue.Dequeue();

                if (current.Left != null)
                    queue.Enqueue(current.Left);
                if (current.Right != null)
                    queue.Enqueue(current.Right);

                var count = counts[current.Key];
                for (int i = 0; i < count; i++)
                    yield return current;
            }
        }

        public IEnumerable<BSTNode<TKey, TValue>> DFS()
        {
            if (Root == null)
                yield break;

            var stack = new Stack<BSTNode<TKey, TValue>>();
            stack.Push(Root);

            while (stack.Count > 0)
            {
                var current = stack.Pop();

                if (current.Right != null)
                    stack.Push(current.Right);
                if (current.Left != null)
                    stack.Push(current.Left);

                var count = counts[current.Key];
                for (int i = 0; i < count; i++)
                    yield return current;
            }
        }
    }
}