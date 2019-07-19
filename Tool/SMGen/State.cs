using System;

namespace xelous
{
    public class State
    {
        private string mName;

        public State(string pName)
        {
            mName = pName;
        }

        public string Name
        {
            get { return mName; }
            set { mName = value; }
        }

        public override string ToString()
        {
            return "State: " + mName;
        }
    }
}