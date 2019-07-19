using System;
using System.Collections.Generic;

namespace xelous
{
    public class StateMachine
    {
        private string mName;
        private List<string> mStates = new List<string>();

        public StateMachine(string pName)
        {
            mName = pName.Replace(' ', '_');
        }

        public string Name
        {
            get { return mName; }
            set { mName = value; }
        }

        public override string ToString()
        {
            string temp = "StateMachine: " + mName;
            if ( mStates.Count == 0 )
            {
                temp += " (No States)";
            }
            return temp;
        }
    }
}