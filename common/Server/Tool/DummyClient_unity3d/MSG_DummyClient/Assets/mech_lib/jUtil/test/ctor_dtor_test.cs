using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class AAA
{
	string name;
	public AAA(string a) { name = a; }
	~AAA() { Debug.Log("~AAA() = " + name); }
}

public class ctor_dtor_test : MonoBehaviour
{


	// Use this for initialization
	void Start()
	{

		System.Object o = null;
		{
			AAA a = new AAA("a1");
			o = a;
		}
		AAA b = new AAA("a2");
		o = b;
		Debug.Log("o.RefCount = " + o.GetType());
	}

	// Update is called once per frame
	void Update()
	{

	}
}
