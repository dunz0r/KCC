using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;


/// <summary>
/// Outputs data
///jj </summary>
public class Testmodule : PartModule
{
	/// <summary>
	/// Raises the start event.
	/// </summary>
	/// <param name="state">State.</param>
	public override void OnStart(StartState state)
	{
		print ("Plugin loaded");
	}
}
