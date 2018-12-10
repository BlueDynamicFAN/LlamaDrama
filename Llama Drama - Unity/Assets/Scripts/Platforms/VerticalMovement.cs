using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VerticalMovement : MonoBehaviour
{
    private Vector3 startPos;
    private Vector3 targetPos;
    public float speed;
    private bool moveUp;
    private GameObject target = null;
    private Vector3 offset;

    void Start()
    {
        startPos = transform.position;
        targetPos = new Vector3(startPos.x, startPos.y + 23, startPos.z);
        moveUp = true;
    }

    void Update()
    {
        float step = speed * Time.deltaTime;
        if (transform.position == targetPos)
        {
            moveUp = false;
        }
        else if (transform.position == startPos)
        {
            moveUp = true;
        }
        if (moveUp == false)
        {
            transform.position = Vector3.MoveTowards(transform.position, startPos, step);
        }
        else if (moveUp)
        {
            transform.position = Vector3.MoveTowards(transform.position, targetPos, step);
        }
    }

    private void OnTriggerStay2D(Collider2D collision)
    {
        target = collision.gameObject;
        offset = target.transform.position - transform.position;
    }

    void OnTriggerExit2D(Collider2D col)
    {
        target = null;
    }

    void LateUpdate()
    {
        if (target != null)
        {
            target.transform.position = transform.position + offset;
        }
    }

}