using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;


// <summary>
// Outputs data
// </summary>
public class Testmodule : PartModule
{
	public override void OnStart(StartState state)
	{
		print ("something to log");
	}
}
